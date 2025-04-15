#include "phone_book.h"


PhoneBook::PhoneBook(std::vector<Contact> contacts) : contact_book(contacts) {
    std::sort(contact_book.begin(), contact_book.end());
};

PhoneBook::ContactRange PhoneBook::FindByNamePrefix(std::string_view name_prefix) const {
    if (name_prefix.empty()) {
        return ContactRange(std::begin(contact_book), std::end(contact_book));
    }
    
    if (contact_book.empty()) {
        return ContactRange(std::end(contact_book), std::end(contact_book));
    }

    CompareContacts compare_contacts(name_prefix);
    
    Contact check_prefix;
    check_prefix.name = std::string(name_prefix);

    auto it_lower = std::lower_bound(std::begin(contact_book), std::end(contact_book), check_prefix, compare_contacts);
    auto it_upper = std::upper_bound(it_lower, std::end(contact_book), check_prefix, compare_contacts);

    return ContactRange(it_lower, it_upper);
}

void PhoneBook::SaveTo(std::ostream& output) const {
    PhoneBookSerialize::ContactList contact_list;
    for(const auto& contact : contact_book){
        PhoneBookSerialize::Contact* pb_contact = contact_list.add_contact();
        pb_contact->set_name(contact.name);
        if(contact.birthday.has_value()){
            PhoneBookSerialize::Date* pb_date = pb_contact->mutable_birthday();
            pb_date->set_year(contact.birthday->year);
            pb_date->set_month(contact.birthday->month);
            pb_date->set_day(contact.birthday->day);
        }
        
        for(const auto& phone : contact.phones){
            pb_contact->add_phone_number(phone);
        }
    }

    contact_list.SerializeToOstream(&output);
};


PhoneBook DeserializePhoneBook(std::istream& input){
    PhoneBookSerialize::ContactList contact_list;
    if(!contact_list.ParseFromIstream(&input)){
        throw std::runtime_error("Failed to parse phone book from input stream");
    }
    std::vector<Contact> contacts;
    contacts.reserve(contact_list.contact_size());
    for (const auto& pb_contact : contact_list.contact()){
        Contact contact;
        contact.name = pb_contact.name();
        if(pb_contact.has_birthday()){
            contact.birthday = std::make_optional<Date>(pb_contact.birthday().year(), pb_contact.birthday().month(), pb_contact.birthday().day());
        }
        for(const auto& phone : pb_contact.phone_number()){
            contact.phones.push_back(phone);
        }
        contacts.push_back(contact);
    }
    return PhoneBook(contacts);

}