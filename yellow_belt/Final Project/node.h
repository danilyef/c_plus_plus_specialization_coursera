#pragma once
#include <memory>
#include "date.h"


enum class Comparison {
    Less,
    LessOrEqual,
    Greater,
    GreaterOrEqual,
    Equal,
    NotEqual
};

enum class LogicalOperation {
    And, Or
};


using namespace std;

class Node {
public:
    virtual bool Evaluate(const Date& date, const std::string& event) const = 0;
    
};

class EmptyNode : public Node{
public:
    EmptyNode();
    bool Evaluate(const Date& date, const std::string& event) const override;

private:

};

class DateComparisonNode : public Node{
public:
    DateComparisonNode(const Comparison& cmp, const Date& date);
    bool Evaluate(const Date& date, const std::string& event) const override;

private:
    const Comparison cmp_;
    const Date date_;
};

class EventComparisonNode : public Node{
public:
    EventComparisonNode(const Comparison& cmp, const std::string event);
    bool Evaluate(const Date& date, const std::string& event) const override;

private:
    const Comparison cmp_;
    const std::string event_;
};

class LogicalOperationNode : public Node{
public:
    LogicalOperationNode(const LogicalOperation& logical_operation,shared_ptr<Node> left,shared_ptr<Node> right);
    bool Evaluate(const Date& date, const std::string& event) const override;

private: 
    const LogicalOperation log_op_;
    const shared_ptr<Node> left_;
    const shared_ptr<Node> right_;

};