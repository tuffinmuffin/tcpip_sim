#include "graph.h"



std::ostream& operator<<( std::ostream &output, const Interface &intf) {
        output << "  Link (attached " << intf.parent_.getName() << "): " << intf.name_ << " :: " ;
        output << intf.link_->getLink(true).getParent().getName() << "_" << *intf.link_ << "_" << intf.link_->getLink(false).getParent().getName();
        output << " ( cost = " << intf.link_->getCost() << " )" << std::endl;

        return output;
}

 std::ostream& operator<<( std::ostream &output, const Link &link) {
     return output << link.interface0_.getName() << " <-> " << link.interface1_.getName();
 }