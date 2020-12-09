//header TODO

#pragma once

#include <string>
#include <iostream>
#include <memory>
#include <cstdint>
#include <map>

using std::map;
using std::string;
using std::shared_ptr;
using std::unique_ptr;
using std::make_shared;

#if 0
#define IF_NAME_SIZE (32)
#define MAX_INTF_PER_NODE (16);
#define NODE_NAME_SIZE (32);

struct node_t;
struct link_t;
struct interface_t;

struct interface_t {
    char if_name[IF_NAME_SIZE];
    struct node_t* att_node;
    struct link_t *link;
};

struct link_t {
    struct interface_t intf1;
    struct interface_t intf2;
    uint32_t    cost;
}

struct node_t {
    char node_name[NODE_NAME_SIZE];
    struct interface_t* intf[MAX_INTF_PER_NODE];
};

typedef struct graph_t{
    char topology_name[32];
    std::list<struct node_t*> node_list;
};
#endif
class Interface;
class Node;
class Graph;
class Link;

class Link
{
public:
    Link(Interface &link0, Interface &link1, uint32_t cost = 0) : interface0_(link0), interface1_(link1), cost_(cost)
    {
    }

    Interface& getLink(bool which) { return which ? interface0_ : interface1_;}
    uint32_t getCost() {return cost_;};

    friend std::ostream& operator<<( std::ostream &output, const Link &link);

private:
    Interface &interface0_;
    Interface &interface1_;
    uint32_t cost_;
};

class Interface
{
public:
    Interface(Node &parent, string name) : name_(name), parent_(parent), link_(nullptr)
    {
    }

    void linkTo(Interface& interface, uint32_t cost = 0) {
        link_ = std::make_shared<Link>(*this, interface, cost);
        interface.assignLink(link_);
    }

    friend std::ostream& operator<<( std::ostream &output, const Interface &intf);

    shared_ptr<Link> getLink() { return link_;}

    const string& getName() { return name_;}

    Node& getParent() { return parent_; }

protected:
    void assignLink(shared_ptr<Link> link) {
        link_ = link;
    }

private:
    string name_;
    Node &parent_;
    shared_ptr<Link> link_;
};

class Node
{
public:
    Node(string name) : name_(name), node_list_()
    {
    }

    Interface& attachInterface(string name) {
        //node_list_.push_back(interface);
        if(node_list_.count(name) == 0) {
            //auto new_node = std::make_unique<Node>(name);
            node_list_.insert(std::make_pair(name, unique_ptr<Interface>(new Interface(*this, name))));
        } else {
            std::cout << name << "Already exsists. Skipping" << std::endl;
        }
        return getInterface(name);
    }

    Interface& getInterface(string name) {
        return *node_list_[name].get();
    }

    friend std::ostream &operator<<( std::ostream &output, const Node &n) {
        std::cout << "Node: " << n.name_ << std::endl;
        for( auto &intf : n.node_list_) {
            std::cout << "  Interface: " << intf.first << std::endl;
            std::cout << "     " << *intf.second << std::endl;
        }

        return output;
    }

    const string& getName() { return name_; }

private:
    string name_;
    map<string, shared_ptr<Interface>> node_list_;
};


class Graph
{
    static const int kNameIdx = 0;
    static const int kNodeIdx = 1;
public:
    Graph(string name): name_(name), nodes_()
    {
    }

    Node& insertNode(string name) {
        if(nodes_.count(name) == 0) {
            //auto new_node = std::make_unique<Node>(name);
            nodes_.insert(std::make_pair(name, unique_ptr<Node>(new Node(name))));
        } else {
            std::cout << name << "Already exsists. Skipping" << std::endl;
        }
        return getNode(name);
    }

    Node& getNode(const string name) {
        return *nodes_[name].get();
    }

    Node& operator[](const string name) {
        return getNode(name);
    }

    Node& operator[](const char* name) {
        return getNode(string(name));
    }

    shared_ptr<Link> attachNodes(const string nodeName0, const string nodeName1, const string interfaceName0, const string interfaceName1, int cost) {
        Node& node0 = getNode(nodeName0);
        Node& node1 = getNode(nodeName1);
        Interface& interface0 = node0.attachInterface(interfaceName0);
        Interface& interface1 = node1.attachInterface(interfaceName1);
        interface0.linkTo(interface1);

        return interface0.getLink();
    }

    friend std::ostream &operator<<( std::ostream &output, const Graph &g) {
        output << "Network: " << g.name_ << "Nodes " << g.nodes_.size() <<std::endl;
        for( auto &node : g.nodes_) {
            //std::cout << "  Node: " << node.first << std::endl;
            output << *node.second << std::endl;
        }

        return output;
    }
    

private:
    string name_;
    map<string, unique_ptr<Node>> nodes_;
};
