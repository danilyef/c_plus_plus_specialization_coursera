#pragma once

#include <cstdint>
#include <string>
#include <ostream>
#include <iostream>
#include <variant>
#include <vector>
#include <memory>
#include "json.h"


namespace Svg {

struct Point {
    Point() : x(0.0), y(0.0) {};
    Point(double x, double y) : x(x), y(y) {};
    double x;
    double y;
};


struct Rgb {
    Rgb() : red(0), green(0), blue(0) {};
    Rgb(uint8_t red, uint8_t green, uint8_t blue) : red(red), green(green), blue(blue) {};
    uint8_t red;
    uint8_t green;
    uint8_t blue;
};

struct Rgba {
    Rgba() : red(0), green(0), blue(0), alpha(0) {};
    Rgba(uint8_t red, uint8_t green, uint8_t blue, double alpha) : red(red), green(green), blue(blue), alpha(alpha) {};
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    double alpha;
};



class Color {
public:
    Color();
    Color(const char* color);
    Color(const std::string& color);
    Color(Rgb rgb);
    Color(Rgba rgba);
    std::string ToString() const;
    static Color ToColor(const Json::Node& color_node);
private:
    std::variant<std::monostate, std::string, Rgb, Rgba> color_;
    friend std::ostream& operator<<(std::ostream& os, const Color& color);
};

extern const Color NoneColor;

class Shape {
public:
    virtual ~Shape() = default;
    virtual std::string Render() const = 0;
};

template <typename Derived>
class Shape_T : public Shape{
public:
    
    Shape_T() : fill_color_(NoneColor), stroke_color_(NoneColor), stroke_width_(1.0) {};

    Derived& SetFillColor(const Color& color) & {
        fill_color_ = color;
        return *static_cast<Derived*>(this);
    }
    Derived& SetStrokeColor(const Color& color) & {
        stroke_color_ = color;
        return *static_cast<Derived*>(this);
    }
    Derived& SetStrokeWidth(double width) & {
        stroke_width_ = width;
        return *static_cast<Derived*>(this);
    }
    Derived& SetStrokeLineCap(const std::string& line_cap) & {
        stroke_line_cap_ = line_cap;
        return *static_cast<Derived*>(this);
    }
    Derived& SetStrokeLineJoin(const std::string& line_join) & {
        stroke_line_join_ = line_join;
        return *static_cast<Derived*>(this);
    }

    Derived&& SetFillColor(const Color& color) && {
        fill_color_ = color;
        return std::move(*static_cast<Derived*>(this));
    }
    Derived&& SetStrokeColor(const Color& color) && {
        stroke_color_ = color;
        return std::move(*static_cast<Derived*>(this));
    }
    Derived&& SetStrokeWidth(double width) && {
        stroke_width_ = width;
        return std::move(*static_cast<Derived*>(this));
    }
    Derived&& SetStrokeLineCap(const std::string& line_cap) && {
        stroke_line_cap_ = line_cap;
        return std::move(*static_cast<Derived*>(this));
    }
    Derived&& SetStrokeLineJoin(const std::string& line_join) && {
        stroke_line_join_ = line_join;
        return std::move(*static_cast<Derived*>(this));
    }



protected:
    Color fill_color_;
    Color stroke_color_;
    double stroke_width_;
    std::string stroke_line_cap_;
    std::string stroke_line_join_;
};

class Circle : public Shape_T<Circle>{
public:
    Circle();
    Circle& SetCenter(const Point& center) &;
    Circle& SetRadius(double radius) &;
    
    Circle&& SetCenter(const Point& center) &&;
    Circle&& SetRadius(double radius) &&;
    
    std::string Render() const override;
private:
    Point center_;
    double radius_;
};

class Polyline : public Shape_T<Polyline>{
public: 
    Polyline();
    Polyline& AddPoint(const Point& point) &;
    Polyline&& AddPoint(const Point& point) &&;
    std::string Render() const override;
private:
    std::vector<Point> points;
};

class Text : public Shape_T<Text>{
public:
    Text();
    Text& SetPoint(const Point& point) &;
    Text& SetOffset(const Point& offset) &;
    Text& SetFontSize(uint32_t font_size) &;
    Text& SetFontFamily(const std::string& font_family) &;
    Text& SetData(const std::string& data) &;

    Text&& SetPoint(const Point& point) &&;
    Text&& SetOffset(const Point& offset) &&;
    Text&& SetFontSize(uint32_t font_size) &&;
    Text&& SetFontFamily(const std::string& font_family) &&;
    Text&& SetData(const std::string& data) &&;

    std::string Render() const override;

private:
    Point point_;
    Point offset_;
    uint32_t font_size_;
    std::string font_family_;
    std::string data_;
};



class Document{

public:
    Document();
    Document& Add(const Polyline& polyline) &;
    Document& Add(const Circle& circle) &;
    Document& Add(const Text& text) &;
    Document& Add(Polyline&& polyline) &;
    Document& Add(Circle&& circle) &;
    Document& Add(Text&& text) &;
    
        // Rvalue overloads that allow method chaining on Document temporaries
    Document&& Add(const Polyline& polyline) &&;
    Document&& Add(const Circle& circle) &&;
    Document&& Add(const Text& text) &&;
    Document&& Add(Polyline&& polyline) &&;
    Document&& Add(Circle&& circle) &&;
    Document&& Add(Text&& text) &&;
    
    void Render(std::ostream& out) const;
    std::string RenderToString() const;
    bool SaveToFile(const std::string& filename) const;

private:
    std::vector<std::shared_ptr<const Shape>> shapes;
};

}