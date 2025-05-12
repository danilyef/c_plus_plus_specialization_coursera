#include "svg.h"
#include <memory>
#include <fstream>

namespace Svg {

Color::Color() : color_(std::monostate()) {};
Color::Color(const char* name) : color_(name) {};
Color::Color(const std::string& name) : color_(name) {};
Color::Color(Rgb rgb) : color_(rgb) {};
Color::Color(Rgba rgba) : color_(rgba) {};

Color Color::ToColor(const Json::Node& color_node){
   if(color_node.is<std::vector<Json::Node>>()){
        const auto& color_array = color_node.AsArray();
        if(color_array.size() == 4){
            Svg::Rgba rgba(color_array[0].AsInt(), color_array[1].AsInt(), color_array[2].AsInt(), color_array[3].AsDouble());
            return Svg::Color(rgba);
        } else if (color_array.size() == 3){
            Svg::Rgb rgb(color_array[0].AsInt(), color_array[1].AsInt(), color_array[2].AsInt());
            return Svg::Color(rgb);
        } else {
            throw std::invalid_argument("Invalid underlayer color");
        }
    } else {
        return Svg::Color(color_node.AsString());
    }
}


std::string Color::ToString() const {
    if (std::holds_alternative<Rgb>(color_)) {
        const Rgb& rgb = std::get<Rgb>(color_);
        return "rgb(" + std::to_string(rgb.red) + "," + std::to_string(rgb.green) + "," + std::to_string(rgb.blue) + ")";
    } else if (std::holds_alternative<std::string>(color_)) {
        return std::get<std::string>(color_);
    }  else if (std::holds_alternative<Rgba>(color_)) {
        const Rgba& rgba = std::get<Rgba>(color_);
        return "rgba(" + std::to_string(rgba.red) + "," + std::to_string(rgba.green) + "," + std::to_string(rgba.blue) + "," + std::to_string(rgba.alpha) + ")";
    }
    return "none";
}

std::ostream& operator<<(std::ostream& os, const Color& color) {
    os << color.ToString();
    return os;
}   


const Color NoneColor;


/*Circle Class*/
Circle::Circle() : Shape_T<Circle>(), center_(0.0, 0.0), radius_(1.0) {};

Circle& Circle::SetCenter(const Point& center) & {
    center_ = center;
    return *this;
}
Circle& Circle::SetRadius(double radius) & {
    radius_ = radius;
    return *this;
}   

Circle&& Circle::SetCenter(const Point& center) && {
    center_ = center;
    return std::move(*this);
}   
Circle&& Circle::SetRadius(double radius) && {
    radius_ = radius;
    return std::move(*this);
}   

std::string Circle::Render() const  {
    std::string result = "<circle cx=\\\"" + std::to_string(center_.x) + "\\\" cy=\\\"" + std::to_string(center_.y) + 
           "\\\" r=\\\"" + std::to_string(radius_) + "\\\" fill=\\\"" + fill_color_.ToString() + 
           "\\\" stroke=\\\"" + stroke_color_.ToString() + "\\\" stroke-width=\\\"" + std::to_string(stroke_width_) + "\\\"";
    
    if (!stroke_line_cap_.empty()) {
        result += " stroke-linecap=\\\"" + stroke_line_cap_ + "\\\"";
    }
    
    if (!stroke_line_join_.empty()) {
        result += " stroke-linejoin=\\\"" + stroke_line_join_ + "\\\"";
    }
    
    result += " />";
    return result;
}

/*Polyline Class*/
Polyline::Polyline() : Shape_T<Polyline>() {};

Polyline& Polyline::AddPoint(const Point& point) & {
    points.push_back(point);
    return *this;
}

Polyline&& Polyline::AddPoint(const Point& point) && {
    points.push_back(point);
    return std::move(*this);
}

std::string Polyline::Render() const {
    std::string result = "<polyline points=\\\"";
    for (const auto& point : points) {
        result += std::to_string(point.x) + "," + std::to_string(point.y) + " ";
    }
    
    result += "\\\" fill=\\\"" + fill_color_.ToString() + 
           "\\\" stroke=\\\"" + stroke_color_.ToString() + "\\\" stroke-width=\\\"" + std::to_string(stroke_width_) + "\\\"";
    
    if (!stroke_line_cap_.empty()) {
        result += " stroke-linecap=\\\"" + stroke_line_cap_ + "\\\"";
    }
    
    if (!stroke_line_join_.empty()) {
        result += " stroke-linejoin=\\\"" + stroke_line_join_ + "\\\"";
    }
    
    result += " />";
    return result;
}

/*Text Class*/
Text::Text() : Shape_T<Text>(), point_(0.0, 0.0), offset_(0.0, 0.0), font_size_(1) {};

Text& Text::SetPoint(const Point& point) & {
    point_ = point;
    return *this;
}   
Text& Text::SetOffset(const Point& offset) & {
    offset_ = offset;
    return *this;
}
Text& Text::SetFontSize(uint32_t font_size) & {
    font_size_ = font_size;
    return *this;
}

Text& Text::SetFontFamily(const std::string& font_family) & {
    font_family_ = font_family;
    return *this;
}
Text& Text::SetFontWeight(const std::string& font_weight) & {
    font_weight_ = font_weight;
    return *this;
}

Text& Text::SetData(const std::string& data) & {
    data_ = data;
    return *this;
}

Text&& Text::SetPoint(const Point& point) && {
    point_ = point;
    return std::move(*this);
}   
Text&& Text::SetOffset(const Point& offset) && {
    offset_ = offset;
    return std::move(*this);
}
Text&& Text::SetFontSize(uint32_t font_size) && {
    font_size_ = font_size;
    return std::move(*this);
}

Text&& Text::SetFontFamily(const std::string& font_family) && {
    font_family_ = font_family;
    return std::move(*this);
}
Text&& Text::SetFontWeight(const std::string& font_weight) && {
    font_weight_ = font_weight;
    return std::move(*this);
}

Text&& Text::SetData(const std::string& data) && {
    data_ = data;
    return std::move(*this);
}

std::string Text::Render() const {
    std::string result = "<text x=\\\"" + std::to_string(point_.x) + "\\\" y=\\\"" + std::to_string(point_.y) + 
           "\\\" dx=\\\"" + std::to_string(offset_.x) + "\\\" dy=\\\"" + std::to_string(offset_.y) + 
           "\\\" font-size=\\\"" + std::to_string(font_size_) + "\\\"";
    
    if (!font_family_.empty()) {
        result += " font-family=\\\"" + font_family_ + "\\\"";
    }
    if (!font_weight_.empty()) {
        result += " font-weight=\\\"" + font_weight_ + "\\\"";
    }
    
    result += " fill=\\\"" + fill_color_.ToString() + 
           "\\\" stroke=\\\"" + stroke_color_.ToString() + "\\\" stroke-width=\\\"" + std::to_string(stroke_width_) + "\\\"";
    
    if (!stroke_line_cap_.empty()) {
        result += " stroke-linecap=\\\"" + stroke_line_cap_ + "\\\"";
    }
    
    if (!stroke_line_join_.empty()) {
        result += " stroke-linejoin=\\\"" + stroke_line_join_ + "\\\"";
    }
    
    result += ">" + data_ + "</text>";
    return result;
}

Document::Document(){}



// Implementations for the overloaded Add methods
Document& Document::Add(const Polyline& polyline) & {
    shapes.push_back(std::make_shared<Polyline>(polyline));
    return *this;
}

Document& Document::Add(const Circle& circle) & {
    shapes.push_back(std::make_shared<Circle>(circle));
    return *this;
}

Document& Document::Add(const Text& text) & {
    shapes.push_back(std::make_shared<Text>(text));
    return *this;
}

// Rvalue reference overloads for Add methods
Document& Document::Add(Polyline&& polyline) & {
    shapes.push_back(std::make_shared<Polyline>(std::move(polyline)));
    return *this;
}

Document& Document::Add(Circle&& circle) & {
    shapes.push_back(std::make_shared<Circle>(std::move(circle)));
    return *this;
}

Document& Document::Add(Text&& text) & {
    shapes.push_back(std::make_shared<Text>(std::move(text)));
    return *this;
}

// Add implementations for rvalue Document overloads
Document&& Document::Add(const Polyline& polyline) && {
    shapes.push_back(std::make_shared<Polyline>(polyline));
    return std::move(*this);
}

Document&& Document::Add(const Circle& circle) && {
    shapes.push_back(std::make_shared<Circle>(circle));
    return std::move(*this);
}

Document&& Document::Add(const Text& text) && {
    shapes.push_back(std::make_shared<Text>(text));
    return std::move(*this);
}

Document&& Document::Add(Polyline&& polyline) && {
    shapes.push_back(std::make_shared<Polyline>(std::move(polyline)));
    return std::move(*this);
}

Document&& Document::Add(Circle&& circle) && {
    shapes.push_back(std::make_shared<Circle>(std::move(circle)));
    return std::move(*this);
}

Document&& Document::Add(Text&& text) && {
    shapes.push_back(std::make_shared<Text>(std::move(text)));
    return std::move(*this);
}

void Document::Render(std::ostream& out) const {
    out << "<?xml version=\\\"1.0\\\" encoding=\\\"UTF-8\\\" ?>";
    out << "<svg xmlns=\\\"http://www.w3.org/2000/svg\\\" version=\\\"1.1\\\">";
    for (const auto& shape : shapes) {
        out << shape->Render();
    }
    out << "</svg>";
}

std::string Document::RenderToString() const {
    std::stringstream ss;
    Render(ss);
    return ss.str();
}   



bool Document::SaveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    Render(file);
    file.close();
    return true;
}



}


