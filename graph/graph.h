#ifndef _GRAPH_DS_CPP_
#define _GRAPH_DS_CPP_

#include <algorithm>           /* std::max                   */
#include <queue>               /* std::queue                 */
#include <vector>              /* std:vector                 */
#include <stack>               /* std::stack                 */
#include <sstream>             /* std::stringstream          */

namespace graph
{
   
/* Undirected Graph Implementation                           */
<typename ET=int>
class digraph{
public:

private:

};

template<typename Tkey, typename Tval>
std::ostream& operator<<(std::ostream& os, undirected_graph& bin) {
   //pretty_print(bin.get_root());
   os << std::endl;
   return os;
}

} //end namespace

#endif //_GRAPH_DS_CPP_
