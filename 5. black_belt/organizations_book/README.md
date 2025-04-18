

### **Programming Assignment: Organizations Directory**

In this task, you will work with the Yellow Pages project — a directory of organizations on maps. Information about organizations is stored in the protobuf format.

Each organization (`message Company`) is described with the following attributes: address, name, phone number, website, and working hours. Each of these attributes is structured: for the address, in addition to a formatted text description, there are coordinates; names have types; phone numbers include country code, city code, description, and extension; and working hours are represented as a combination of minute intervals on specific days.

Initially, data about organizations comes from various suppliers in the form of signals (`message Signal`). A signal is a description of a particular company from the perspective of a specific data provider. It’s clear that different signals from different providers may in fact describe the same organization. At the same time, these different signals can complement each other: one signal might provide a website, another a phone number, and a third the working hours.

The task of clustering signals into groups where all signals in a group describe the same organization has already been solved for you. Your task is to write a `Merge` function that creates a card (record) for an organization from a set of signals about it. This function should select the attribute values for the organization from the signals. We've written a very primitive version of this function, which simply takes the first signal from the group and uses its organization card.

Your `Merge` function must actually do the following:

- For each attribute, select all signals with the highest priority provider where this attribute is filled in.

- If the attribute is *repeating* (like phone number, name, website), populate the organization card with *different* values of this attribute from the selected signals.

- If the attribute is *non-repeating* (like address, working hours), choose its value from *any* of the selected signals.

You may notice that the code for the `Merge` function is very similar for different attributes. You might want to write it uniformly. You can do this using macros, helper overloaded functions, or by leveraging protobuf’s Reflection capabilities.

--- 

Let me know if you want help writing the `Merge` function or if you need the protobuf schema explained!