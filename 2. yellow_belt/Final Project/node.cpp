#include "node.h"

using namespace std;


//----------------------------------------------------------------------------------------------------
EmptyNode::EmptyNode(){};

bool EmptyNode::Evaluate(const Date& date, const std::string& event) const {
    return true;
};


//----------------------------------------------------------------------------------------------------

DateComparisonNode::DateComparisonNode(const Comparison& cmp, const Date& date) : cmp_(cmp),date_(date){};
bool DateComparisonNode::Evaluate(const Date& date, const std::string& event) const {
    
    if(cmp_ == Comparison::Less){
        return date < date_;
    } else if(cmp_ == Comparison::LessOrEqual){
        return date <= date_;
    } else if(cmp_ == Comparison::Greater){
        return date > date_;
    } else if(cmp_ == Comparison::GreaterOrEqual){
        return date >= date_;
    } else if(cmp_ == Comparison::Equal){
        return date == date_;
    } else if(cmp_ == Comparison::NotEqual){
        return date != date_;
    } else{
         return 0;
    }

};


//----------------------------------------------------------------------------------------------------

EventComparisonNode::EventComparisonNode(const Comparison& cmp, const std::string event) : cmp_(cmp),event_(event){};
bool EventComparisonNode::Evaluate(const Date& date, const std::string& event) const {
    if(cmp_ == Comparison::Equal){
        return event == event_;
    } else if (cmp_ == Comparison::NotEqual){
        return event != event_;
    }else if (cmp_ == Comparison::Less){
        return event < event_;
    }else if (cmp_ == Comparison::LessOrEqual){
        return event <= event_;
    }else if (cmp_ == Comparison::Greater){
        return event > event_;
    }else if (cmp_ == Comparison::GreaterOrEqual){
        return event >= event_;
    } else {
         return 0;
    }
};


//----------------------------------------------------------------------------------------------------

LogicalOperationNode::LogicalOperationNode(const LogicalOperation& logical_operation,shared_ptr<Node> left,shared_ptr<Node> right) :  left_(left),right_(right),log_op_(logical_operation){};
bool LogicalOperationNode::Evaluate(const Date& date, const std::string& event) const {
    if(log_op_ == LogicalOperation::And){
        return (left_->Evaluate(date,event) && right_->Evaluate(date,event));
    } else if(log_op_ == LogicalOperation::Or){
        return (left_->Evaluate(date,event) || right_->Evaluate(date,event));
    } else{
        return 0;
    }
};