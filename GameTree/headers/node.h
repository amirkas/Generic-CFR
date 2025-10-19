#include <stdio.h>
#include <string>
#include <memory>
#include <vector>

#include <infoset.h>
#include <probability_set.h>

template<typename float_type>
class Node {

public:
    virtual ~Node() = default;

    std::shared_ptr<Node> next_node;

    Node();

    explicit Node(std::shared_ptr<Node> next_node_address);

    virtual std::string toString() = 0; 
    
};

template<typename float_type>
class NonTerminalNode : public Node<float_type> {

public:

    std::shared_ptr<Node<float_type>> first_child;
    uint8_t num_children;

    NonTerminalNode();
    explicit NonTerminalNode(std::shared_ptr<Node<float_type>> first_child_p);

    virtual uint8_t NumChildren();

    std::vector<std::shared_ptr<Node<float_type>>> Children() const;

    std::shared_ptr<Node<float_type>> GetChild(uint8_t index);
};
