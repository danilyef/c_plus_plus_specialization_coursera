#include "svg.h"
#include <fstream>

int main() {

    //Example 1: Lvalues example
    Svg::Document svg;

    svg.Add(
        Svg::Polyline{}
        .SetStrokeColor(Svg::Rgb{140, 198, 63}) 
        .SetStrokeWidth(16)
        .SetStrokeLineCap("round")
        .AddPoint({50, 50})
        .AddPoint({250, 250})
    );

    for (const auto point : {Svg::Point{50, 50}, Svg::Point{250, 250}}) {
    svg.Add(
        Svg::Circle{}
        .SetFillColor("white")
        .SetRadius(6)
        .SetCenter(point)
    );
    }

    svg.Add(
        Svg::Text{}
        .SetPoint({50, 50})
        .SetOffset({10, -10})
        .SetFontSize(20)
        .SetFontFamily("Verdana")
        .SetFillColor("black")
        .SetData("C")
    );
    svg.Add(
        Svg::Text{}
        .SetPoint({250, 250})
        .SetOffset({10, -10})
        .SetFontSize(20)
        .SetFontFamily("Verdana")
        .SetFillColor("black")
        .SetData("C++")
    );
    svg.SaveToFile("example_1.svg");


    Svg::Document chainedDoc;
    

    const Svg::Point circle1Center{100, 100};
    const Svg::Point circle2Center{150, 100};
    const Svg::Point circle3Center{200, 100};


    chainedDoc.Add(
        Svg::Polyline{}
        .SetStrokeColor(Svg::Rgb{128, 128, 128})  
        .SetStrokeWidth(3)
        .SetStrokeLineCap("round")
        .SetStrokeLineJoin("round")
        .AddPoint(circle1Center)
        .AddPoint(circle2Center)
        .AddPoint(circle3Center)
    ).Add(
        Svg::Circle{}
        .SetFillColor(Svg::Rgb{255, 0, 0})  
        .SetStrokeColor("black")
        .SetStrokeWidth(2)
        .SetRadius(20)
        .SetCenter(circle1Center)
    ).Add(
        Svg::Circle{}
        .SetFillColor(Svg::Rgb{0, 255, 0})  
        .SetStrokeColor("black")
        .SetStrokeWidth(2)
        .SetRadius(20)
        .SetCenter(circle2Center)
    ).Add(
        Svg::Circle{}
        .SetFillColor(Svg::Rgb{0, 0, 255})  
        .SetStrokeColor("black")
        .SetStrokeWidth(2)
        .SetRadius(20)
        .SetCenter(circle3Center)
    );
    
    chainedDoc.SaveToFile("example_2.svg");
   
    //Example 3: Move semantics with Circles, Polyline, and Text
    Svg::Document moveDoc;
    

    const Svg::Point cppCenter{100, 100};
    const Svg::Point rustCenter{200, 150};
    const Svg::Point pythonCenter{150, 50};

    Svg::Polyline redLines;
    redLines.SetStrokeColor(Svg::Rgb{255, 0, 0}) 
            .SetStrokeWidth(3)
            .SetStrokeLineJoin("round")
            .AddPoint(cppCenter)
            .AddPoint(rustCenter)
            .AddPoint(pythonCenter)
            .AddPoint(cppCenter); 
    
    // Create circles with move semantics
    Svg::Circle cppCircle;
    cppCircle.SetFillColor(Svg::Rgb{25, 118, 210})  
             .SetStrokeColor("black")
             .SetStrokeWidth(2)
             .SetRadius(30)
             .SetCenter(cppCenter);
             
    Svg::Circle rustCircle;
    rustCircle.SetFillColor(Svg::Rgb{244, 81, 30}) 
              .SetStrokeColor("black")
              .SetStrokeWidth(2)
              .SetRadius(30)
              .SetCenter(rustCenter);
              
    Svg::Circle pythonCircle;
    pythonCircle.SetFillColor(Svg::Rgb{255, 213, 0}) 
                .SetStrokeColor("black")
                .SetStrokeWidth(2)
                .SetRadius(30)
                .SetCenter(pythonCenter);
    

    Svg::Text cppText;
    cppText.SetPoint(cppCenter)
           .SetOffset({0, 0})
           .SetFontSize(14)
           .SetFontFamily("Verdana")
           .SetFillColor("white")
           .SetData("C++");
           
    Svg::Text rustText;
    rustText.SetPoint(rustCenter)
            .SetOffset({0, 0})
            .SetFontSize(14)
            .SetFontFamily("Verdana")
            .SetFillColor("white")
            .SetData("Rust");
            
    Svg::Text pythonText;
    pythonText.SetPoint(pythonCenter)
              .SetOffset({0, 0})
              .SetFontSize(14)
              .SetFontFamily("Verdana")
              .SetFillColor("white")
              .SetData("Python");
    
    moveDoc.Add(std::move(redLines))
           .Add(std::move(cppCircle))
           .Add(std::move(rustCircle))
           .Add(std::move(pythonCircle))
           .Add(std::move(cppText))
           .Add(std::move(rustText))
           .Add(std::move(pythonText));
    
    moveDoc.SaveToFile("example_3.svg");
    
    return 0;
}