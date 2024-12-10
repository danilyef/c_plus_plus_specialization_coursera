### Programming Assignment: Refactoring Someone Else's Code

We will continue working with the example where we created a personal finance tracking program and worked with JSON and XML formats. This time, we decided to add the ability to convert a list of expenses from XML to JSON and vice versa. For this, we wrote two functions:

```cpp
Json::Document XmlToJson(const Xml::Document& doc);
Xml::Document JsonToXml(const Json::Document& doc, string root_name);
```

Additionally, we covered them with unit tests in the functions `TestXmlToJson` and `TestJsonToXml`. But there is one problem — all this code was written by a novice who watched all the lectures of our course but, without solving any tasks, immediately started applying the acquired knowledge at work. He approached you for help, handed over his code, and, saying "Something's not compiling," went on vacation. Your task is to put the code of his functions and tests in order, so that they compile and work.

### Details

The function `XmlToJson` expects an input document with the structure `<root><spend amount="2500" category="food"></spend>...</root>`, i.e., the root node contains zero or more nodes with the name "spend" and attributes "amount" and "category". It should return an object of the `Json::Document` class with the structure `[{"amount": 2500, "category": "food"}, ...]`, meaning it's an array containing as many dictionaries as there were `<spend>` nodes in the XML document. In these dictionaries, the node with the key "amount" should be an integer, and the one with the key "category" should be a string. It is guaranteed that in the testing system, only XML documents conforming to the described format will be passed to your function (i.e., handling incorrect input is not required for this task).

The function `JsonToXml` should perform the reverse transformation. Similarly, in our testing system, only JSON documents conforming to the described format will be passed to it.

The tests `TestXmlToJson` and `TestJsonToXml` should not accept empty implementations of the functions `XmlToJson` and `JsonToXml`, as well as implementations violating the output data format. You do not need to add other test cases to the tests; you need to make those that exist compile and work.