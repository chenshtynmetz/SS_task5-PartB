#include "OrgChart.hpp"
#include <string>
#include <vector>
#include <queue>
#include <stack>

namespace ariel{
    //OrgChart constructor
    OrgChart::OrgChart(){
        this->root = NULL;
        this->q = {};
        this->s = {};
    }
    //OrgChart copy constructor
    OrgChart::OrgChart(const OrgChart& other){
        this->root = other.root;
        this->q = other.q;
        this->s = other.s;
    }
    //create new node
    pnode new_node(std::string str){
        pnode n = new node();
        n->name = std::move(str);
        n->sons = {};
        n->level = 1;
        return n;
    }
    //add root to the chart
    OrgChart& OrgChart::add_root(const std::string& n){
        //if the chart dont have root create one
        if(this->root == NULL){
            this->root = new_node(n);
        }
        //if the chart already have root, change his name
        else{
            this->root->name = n;
        }
        return *this;
    }
    //add employee to the chart
    OrgChart& OrgChart::add_sub(const std::string& name1, const std::string& name2){
        //the chart must to contain root
        if(this->root == NULL){
            throw std::runtime_error("add root first");
        }
        //search the boss name
        for(level_order it = begin_level_order(); it != end_level_order(); ++it){
            if(name1 == (*it)){
                pnode curr = it.get_curr();
                //create new node
                pnode n = new_node(name2);
                //update the new node level
                n->level = (curr->level + 1);
                //enter the new node to the current node sons
                curr->sons.push_back(n);
                return *this;
            }
            //if this name alredy exist this error
            if(name2 == (*it)){
                throw std::runtime_error("this employee alredy exists");
            }
        }
        //the boss doesnt exists
        throw std::runtime_error("this boss dosent exists");
    }
    //= operator
    OrgChart& OrgChart::operator=(const OrgChart& other){
        //call to the copy constructor
        OrgChart org = OrgChart(other);
        return *this;
    }
    //pass operator
    OrgChart& OrgChart::operator=(OrgChart&& other)noexcept{
        OrgChart& org = other;
        return *this;
    }
    //ostream operator
    std::ostream& operator<<(std::ostream& os, OrgChart& chart){
        int ind = 1;
        std::cout << "level " << ind << ": ";
        //print all the names by level
        for(OrgChart::level_order it = chart.begin_level_order(); it != chart.end_level_order(); ++it){
            pnode curr = it.get_curr();
            if(curr->level != ind){
                ind++;
                std::cout << std::endl;
                std::cout << "level " << ind << ": ";
            }
            std::cout << curr->name << " ";
        }
        std::cout << std::endl;
        return os;
    }
    //level order constructor
    OrgChart::level_order::level_order(OrgChart& org, bool end_flag = false){
        //the chart cant be empty
        if(org.root == NULL){
            throw std::runtime_error("the chart is empty");
        }
        this->start = org.root;
        this->end_flag = end_flag;
        this->curr = this->start;
        // clear the queue and the stack
        std::queue<Node*> empty_q;
        std::swap(org.q, empty_q);
        std::stack<Node*> empty_s;
        std::swap(org.s, empty_s);
        //order the nodes by level order
        this->order(org);
        this->order_q = org.q;
        this->order_s = org.s;
    }
    //order the nodes by level order, use BFS style
    OrgChart::level_order& OrgChart::level_order::order(OrgChart& org){
        std::queue<Node*> temp_q;
        temp_q.push(this->start);
        while (!temp_q.empty())
        {
            //pop the first node in the temp queue
            this->curr = temp_q.front();
            temp_q.pop();
            //enter him to the real queue
            org.q.push(this->curr);
            org.s.push(this->curr);
            //push all his sons to the temp queue
            unsigned len = this->curr->sons.size();
            for(unsigned i = 0; i<len; i++){
                temp_q.push(this->curr->sons.at(i));
            }
        }
        //push null pointer to the end
        org.s.push(nullptr);
        org.q.push(nullptr);
        //the current node is the start/end by the end flag
        if(this->end_flag){
            this->curr = org.s.top();
        }
        else{
            this->curr = this->start;
        }
        return *this;
    }
    //return pointer to the current node
    pnode OrgChart::level_order::get_curr(){
        return this->curr;
    }
    //return true if the to iterators dont point to the same node
    bool OrgChart::level_order::operator!=(const level_order& lo)const{
        return this->curr != lo.curr;
    }
    //return true if the to iterators point to the same node
    bool OrgChart::level_order::operator==(const level_order& lo)const{
        return this->curr == lo.curr;
    }
    //increament the iterator to the next node
    OrgChart::level_order& OrgChart::level_order::operator++(){
        this->order_q.pop();
        this->curr = this->order_q.front();
        return *this;
    }
    //-> operator
    std::string* OrgChart::level_order::operator->()const{
        level_order* lo = new level_order(*this);
        return &lo->order_q.front()->name;
    }
    //return the name of the current node
    std::string operator*(const OrgChart::level_order& lo){
        return lo.curr->name;
    }
    //ostraem operator
    std::ostream& operator<<(std::ostream& os, const OrgChart::level_order& lo){
        std::cout << lo.curr->name;
        return os;
    }
    //create iterator end point to the start
    OrgChart::level_order OrgChart::begin_level_order(){
        level_order lo(*this);
        return lo;
    }
    //create iterator and point to the end
    OrgChart::level_order OrgChart::end_level_order(){
        level_order lo(*this, true);
        return lo;
    }
    //reverse order constructor
    OrgChart::reversee_order::reversee_order(OrgChart& org, bool end_flag=false){
        //the chart cant be empty
        if(org.root == NULL){
            throw std::runtime_error("the chart is empty");
        }
        this->start = org.root;
        this->end_flag = end_flag;
        this->curr = this->start;
        // clear the queue and the stack
        std::queue<Node*> empty_q;
        std::swap(org.q, empty_q);
        std::stack<Node*> empty_s;
        std::swap(org.s, empty_s);
        //order the nodes by reverse order
        this->order(org);
        this->order_q = org.q;
        this->order_s = org.s;
    }
    //order the nodes by reverse order, use reverse BFS style
    OrgChart::reversee_order& OrgChart::reversee_order::order(OrgChart& org){
        std::queue<Node*> temp_q;
        std::stack<Node*> temp_s;
        temp_q.push(this->start);
        while (!temp_q.empty())
        {
            //pop the first node in the temp queue
            this->curr = temp_q.front();
            temp_q.pop();
            temp_s.push(this->curr);
            int len = this->curr->sons.size();
            //if curr dont have chilren- continue
            if(len == 0){
                continue;
            }
            //push all curr children to the temp queue from the end to the start
            for(int i=(len-1); i>=0; i--){
                temp_q.push(this->curr->sons.at((unsigned)i));
            }
        }
        //move all to the real stack and queue in reverse
        while(!temp_s.empty()){
            this->curr = temp_s.top();
            temp_s.pop();
            org.q.push(this->curr);
            org.s.push(this->curr);
        }
        //push null pointer to the end
        org.s.push(nullptr);
        org.q.push(nullptr);
        //the current node is the start/end by the end flag
        if(this->end_flag){
            this->curr = org.s.top();
        }
        else{
            this->curr = org.q.front();
        }
        return *this;
    }
    //return true if the to iterators dont point to the same node
    bool OrgChart::reversee_order::operator!=(const reversee_order& ro)const{
        return this->curr != ro.curr;
    }
    //return true if the to iterators point to the same node
    bool OrgChart::reversee_order::operator==(const reversee_order& ro)const{
        return this->curr == ro.curr;
    }
    //increament the iterator to the next node
    OrgChart::reversee_order& OrgChart::reversee_order::operator++(){
        this->order_q.pop();
        this->curr = this->order_q.front();
        return *this;
    }
    //-> operator
    std::string* OrgChart::reversee_order::operator->()const{
        reversee_order* ro = new reversee_order(*this);
        return &ro->order_q.front()->name;
    }
    //return the name of the current node
    std::string operator*(const OrgChart::reversee_order& ro){
        return ro.curr->name;
    }
    //ostraem operator
    std::ostream& operator<<(std::ostream& os, const OrgChart::reversee_order& ro){
        std::cout << ro.curr->name;
        return os;
    }
    //create iterator end point to the start
    OrgChart::reversee_order OrgChart::begin_reverse_order(){
        reversee_order ro(*this);
        return ro;
    }
    //create iterator and point to the end
    OrgChart::reversee_order OrgChart::reverse_order(){
        reversee_order ro(*this, true);
        return ro;
    }
    //preorder constructor
    OrgChart::preorder::preorder(OrgChart& org, bool end_flag=false){
        //the chart cant be empty
        if(org.root == NULL){
            throw std::runtime_error("the chart is empty");
        }
        this->start = org.root;
        this->end_flag = end_flag;
        this->curr = this->start;
        // clear the queue and the stack
        std::queue<Node*> empty_q;
        std::swap(org.q, empty_q);
        std::stack<Node*> empty_s;
        std::swap(org.s, empty_s);
        //order the nodes by preorder
        this->order(org.root, org);
        this->order_q = org.q;
        this->order_s = org.s;
    }
    //order the nodes by reverse order, use DFS style
    OrgChart::preorder& OrgChart::preorder::order(pnode head, OrgChart& org){
        //enter the curren to the queue
        org.q.push(head);
        org.s.push(head);
        unsigned len = head->sons.size();
        //for all the current sons- call again to this function
        for(unsigned i=0; i<len; i++){
            order(head->sons.at(i), org);
        }
        if(head == org.q.front()){
            //push null pointer to the end
            org.s.push(nullptr);
            org.q.push(nullptr);
        }
        //the current node is the start/end by the end flag
        if(this->end_flag){
            this->curr = org.s.top();
        }
        else{
            this->curr = this->start;
        }
        return *this; 
    }
    //return true if the to iterators dont point to the same node
    bool OrgChart::preorder::operator!=(const preorder& pr)const{
        return this->curr != pr.curr;
    }
    //return true if the to iterators point to the same node
    bool OrgChart::preorder::operator==(const preorder& pr)const{
        return this->curr == pr.curr;
    }
    //increament the iterator to the next node
    OrgChart::preorder& OrgChart::preorder::operator++(){
        this->order_q.pop();
        this->curr = this->order_q.front();
        return *this;
    }
    //-> operator
    std::string* OrgChart::preorder::operator->()const{
        preorder* pr = new preorder(*this);
        return &pr->order_q.front()->name;
    }
    //return the name of the current node
    std::string operator*(const OrgChart::preorder& pr){
        return pr.curr->name;
    }
    //ostraem operator
    std::ostream& operator<<(std::ostream& os, const OrgChart::preorder& pr){
        std::cout << pr.curr->name;
        return os;
    }
    //create iterator end point to the start
    OrgChart::preorder OrgChart::begin_preorder(){
        preorder pr(*this);
        return pr;
    }
    //create iterator and point to the end
    OrgChart::preorder OrgChart::end_preorder(){
        preorder pr(*this, true);
        return pr;
    }
    //create iterator end point to the start
    OrgChart::level_order OrgChart::begin(){
        return this->begin_level_order();
    }
    //create iterator and point to the end
    OrgChart::level_order OrgChart::end(){
        return this->end_level_order();
    }
    //destructor
    OrgChart::~OrgChart(){
        erase(this->root);
    }
    //in this function i adviced with my friend rivka boskila
    //erase the chart
    void OrgChart::erase(pnode temp){
        if(temp == nullptr){
            return;
        }
        //for all the temp node sons call again to this function
        for(unsigned long i=0; i< temp->sons.size(); ++i){
            erase((temp->sons.at(i)));
        }
        //delete the temp node
        delete temp;
    }
}