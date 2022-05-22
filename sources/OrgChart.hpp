#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>

namespace ariel{
    //node struct
    typedef struct Node{
        std::string name;
        std::vector<Node*> sons;
        int level;
    }node, *pnode;
    //create new node
    pnode new_node(std::string str);

    class OrgChart{
        private:
            pnode root;
            std::queue<Node*> q;
            std::stack<Node*> s;
        public:
            //constructor
            OrgChart();
            //copy constructor
            OrgChart(const OrgChart& other);
            //destructor
            ~OrgChart();
            //add root to the orgchart
            OrgChart& add_root(const std::string& name);
            //add son to node
            OrgChart& add_sub(const std::string& name1, const std::string& name2);
            //operator =
            OrgChart& operator=(const OrgChart& other);
            //pass operator 
            OrgChart& operator=(OrgChart&& other)noexcept;
            // ostream operator
            friend std::ostream& operator<<(std::ostream& os, OrgChart& chart);
            //level order iterator
            class level_order{
                private:
                    pnode start;
                    std::stack<Node*> order_s;
                    std::queue<Node*> order_q;
                    bool end_flag;
                    pnode curr;
                public:
                    //constructor
                    level_order(OrgChart& org, bool end_flag);
                    // get the current node
                    pnode get_curr();
                    //order the nodes
                    level_order& order(OrgChart& org);
                    // != operator
                    bool operator!=(const level_order& lo)const;
                    //== operator
                    bool operator==(const level_order& lo)const;
                    //++ operator
                    level_order& operator++();
                    //-> operator
                    std::string* operator->()const;
                    // * operator
                    friend std::string operator*(const level_order& lo);
                    // ostream operator
                    friend std::ostream& operator<<(std::ostream& os, const level_order& lo);

            };
            // return the start point
            OrgChart::level_order begin_level_order();
            // return the end point
            OrgChart::level_order end_level_order();
            // reverse order iterator
            class reversee_order{
                private:
                    pnode start;
                    pnode curr;
                    std::stack<Node*> order_s;
                    std::queue<Node*> order_q;
                    bool end_flag;
                public:
                    // constructor
                    reversee_order(OrgChart& org, bool end_flag);
                    //order the nodes
                    reversee_order& order(OrgChart& org);
                    //!= operator
                    bool operator!=(const reversee_order& ro)const;
                    //== operator
                    bool operator==(const reversee_order& ro)const;
                    //++ operator
                    reversee_order& operator++();
                    //-> operator
                    std::string* operator->()const;
                    //* operator
                    friend std::string operator*(const reversee_order& ro);
                    // ostream operator
                    friend std::ostream& operator<<(std::ostream& os, const reversee_order& ro);

            };
            // return the start point
            OrgChart::reversee_order begin_reverse_order();
            // return the end point
            OrgChart::reversee_order reverse_order(); //add end
            //preorder iterator
            class preorder{
                private:
                    pnode start;
                    pnode curr;
                    std::stack<Node*> order_s;
                    std::queue<Node*> order_q;
                    bool end_flag;
                public:
                    //constructor
                    preorder(OrgChart& org, bool end_flag);
                    //order the nodes
                    preorder& order(pnode head, OrgChart& org);
                    // != operator
                    bool operator!=(const preorder& pr)const;
                    // == operator
                    bool operator==(const preorder& pr)const;
                    // ++ operator
                    preorder& operator++();
                    //-> operator
                    std::string* operator->()const;
                    // * operator
                    friend std::string operator*(const preorder& pr);
                    // ostream operator
                    friend std::ostream& operator<<(std::ostream& os, const preorder& pr);
            };
            // return the start point
            preorder begin_preorder();
            // return the end point
            preorder end_preorder();
            // return the start point
            OrgChart::level_order begin();
            // return the end point
            OrgChart::level_order end();
            // erase node
            void erase(pnode temp);
    };
}