// Datastructures.hh

#ifndef DATASTRUCTURES_HH
#define DATASTRUCTURES_HH

#include <string>
#include <vector>
#include <utility>
#include <limits>
#include <unordered_map>
#include <memory>
#include <set>
#include <unordered_set>
#include <map>
#include <queue>

// Type for beacon IDs
using BeaconID = std::string;
using BeaconName = std::string;
using isVisited = bool;
using Parent = std::pair<unsigned int, unsigned int>;

// Return value for cases where required beacon was not found
BeaconID const NO_ID = "----------";

// Return value for cases where integer values were not found
int const NO_VALUE = std::numeric_limits<int>::min();

// Return value for cases where name values were not found
std::string const NO_NAME = "-- unknown --";

// Type for a coordinate (x, y)
struct Coord {
    int x = NO_VALUE;
    int y = NO_VALUE;
};

// Example: Defining == and hash function for Coord so that it can be used
// as key for std::unordered_map/set, if needed
inline bool operator==(Coord c1, Coord c2) { return c1.x == c2.x && c1.y == c2.y; }

inline bool operator!=(Coord c1, Coord c2) { return !(c1 == c2); } // Not strictly necessary

struct CoordHash {
    std::size_t operator()(Coord xy) const {
        auto hasher = std::hash<int>();
        auto xhash = hasher(xy.x);
        auto yhash = hasher(xy.y);
        // Combine hash values (magic!)
        return xhash ^ (yhash + 0x9e3779b9 + (xhash << 6) + (xhash >> 2));
    }
};

// Example: Defining < for Coord so that it can be used
// as key for std::map/set
inline bool operator<(Coord c1, Coord c2) {
    if (c1.y < c2.y) { return true; }
    else if (c2.y < c1.y) { return false; }
    else { return c1.x < c2.x; }
}

// Return value for cases where coordinates were not found
Coord const NO_COORD = {NO_VALUE, NO_VALUE};

// Type for color (RGB)
struct Color {
    int r = NO_VALUE;
    int g = NO_VALUE;
    int b = NO_VALUE;
};


struct lightbeam {
    std::vector<unsigned int> NoS;
    unsigned int NoI;
    unsigned int NoT;
    int dist;
    Color color;
};

struct BeaconData {
    std::vector<unsigned int> NoS;
    unsigned int NoI;
    unsigned int NoT;
    std::string name;
    std::vector<BeaconID> src;
    BeaconID id;
    Coord xy;
    Color color;
    double brightness;
    int dist;
    BeaconID tgt;
};


using fib = std::pair<Coord, Coord>;
// Equality and non-equality comparisons for Colors
inline bool operator==(Color c1, Color c2) { return c1.r == c2.r && c1.g == c2.g && c1.b == c2.b; }

inline bool operator!=(Color c1, Color c2) { return !(c1 == c2); }

// Return value for cases where color was not found
Color const NO_COLOR = {NO_VALUE, NO_VALUE, NO_VALUE};

// Type for light transmission cost (used only in the second assignment)
using Cost = int;

// Return value for cases where cost is unknown
Cost const NO_COST = NO_VALUE;

struct Xpoint {
    Coord point;
    Coord prev;
    Cost total;
};

struct Fibre {
    Coord xpoint1;
    Coord xpoint2;
    Cost cost;
};

struct CompareFirst
{
    CompareFirst(Coord& ff): ff_(ff){}
    bool operator()(const struct Fibre &f)
    {return f.xpoint1 == ff_;}
    Coord &ff_;
};

struct CompareSecond
{
    CompareSecond(Coord& fs): fs_(fs){}
    bool operator()(const struct Fibre &f)
    {return f.xpoint2 == fs_;}
    Coord &fs_;
};

struct fibre_comp
{
    bool operator()(const struct Fibre &f1, const struct Fibre &f2)
    {
        if (f1.xpoint1 < f2.xpoint1) { return true; }
        else if (f2.xpoint1< f1.xpoint1) { return false; }
        else { return f1.xpoint2< f2.xpoint2; }
    }
};

struct fib_comp
{
    bool operator()(const fib &f1, const fib &f2)
    {
       if (f1.first < f2.first) { return true; }
       else if (f2.first< f1.first) { return false; }
       else { return f1.second< f2.second; }
    }
};

// This is the class you are supposed to implement

class Datastructures {
public:
    Datastructures();

    ~Datastructures();

    // Estimate of performance:Theta(n)
    // Short rationale for estimate: It is a linear computation. Returning the size of the beaconlist only.

    int beacon_count();

    // Estimate of performance:Theta(n)
    // Short rationale for estimate:Similar as the beacon count, it simply go over the whole beaconlist.

    void clear_beacons();

    // Estimate of performance:Theta(1)
    // Short rationale for estimate: Again, similar as the clear_beacons, it simply go ovrf the whole beaconlist and return the id.

    std::vector<BeaconID> all_beacons();

    // Estimate of performance:Theta(n)
    // Short rationale for estimate:It is a constant computation. Only to push the new beacon without any sorting or inserting.

    bool add_beacon(BeaconID id, std::string const &name, Coord xy, Color color);

    // Estimate of performance:Theta(n)
    // Short rationale for estimate:It is based on find beacons with one more operation return the coordinate.

    std::string get_name(BeaconID id);

    // Estimate of performance:Theta(n)
    // Short rationale for estimate:Similar as get_name and coordinate, it is based on find beacons with one more operation return the color.

    Coord get_coordinates(BeaconID id);

    // Estimate of performance:O(nlog(n))
    // Short rationale for estimate:If the memory is enough, the For the sorting part,the complexity is linear computation and thus the time complexity is O(nlog(n)) while
    // if the memory is not enough,it will become worse which is O(nlog²(n)).

    Color get_color(BeaconID id);

    // We recommend you implement the operations below only after implementing the ones above

    // Estimate of performance:O(nlog(n))
    // Short rationale for estimate:Similar as the sort on name alphabeticaloly. Only difference is adding the compaire by brightness which is beased on color instead of the name.
    //Thus the complexity of the average case is O(nlog(n)) if memory is enough while as worse as O(nlog²(n)) when memory is not enough.

    std::vector<BeaconID> beacons_alphabetically();

    // Estimate of performance:O(1)
    // Short rationale for estimate:Search  of elements have average constant-time complexity. Incrementing an iterator is constant time so after sort already, the complexity of pure
    // getting the min_brightness which is the first elements will be O(1)

    std::vector<BeaconID> beacons_brightness_increasing();

    // Estimate of performance:O(n)
    // Short rationale for estimate:Search of elements have average constant-time complexity. Incrementing an iterator is constant time so after sort already, the complexity of pure
    // getting the min_brightness which is the largest elements will be O(n)

    BeaconID min_brightness();

    // Estimate of performance:Theta(n)
    // Short rationale for estimate:Consider the search on general case which is implemented on unsorted list,the average complesity will be theta(n) while the best performance will
    // be theta(1) if the beacon is found at the first one. In the worst case, no common elements in the arrays or the last elements are the same making the performance to be theta(n²).

    BeaconID max_brightness();

    // Estimate of performance:Theta(n)
    // Short rationale for estimate:It is based on find_beacons, but with one more step to change the name into new one. Thus, complexity is theta(n)*theta(1) which is still theta(n).

    std::vector<BeaconID> find_beacons(std::string const &name);

    // Estimate of performance:Theta(n)
    // Short rationale for estimate:Basically the same as change_beacon_name,changing the operation as chaging the color. Thus, the complexity is still theta(n).

    bool change_beacon_name(BeaconID id, std::string const &newname);

    // Estimate of performance:O(n)
    // Short rationale for estimate:In our case, we use the adjacency list structure for graphs.
    // It searches n times averagely on the adjList according to source id and then adding target id as the edge member.

    bool change_beacon_color(BeaconID id, Color newcolor);

    // We recommend you implement the operations below only after implementing the ones above

    // Estimate of performance:O(n)
    // Short rationale for estimate:In our case, we use the adjacency list structure for graphs.
    // It searches n times averagely on the adjList according to source id and then adding target id as the edge member.

    bool add_lightbeam(BeaconID sourceid, BeaconID targetid);

    // Estimate of performance:Theta(n)
    // Short rationale for estimate:In my case, I use the adjacency list structure for graphs.
    // It is then the same as the search in the adjList and return the target id everytime.

    std::vector<BeaconID> get_lightsources(BeaconID id);

    // Estimate of performance:O(n)
    // Short rationale for estimate: In my case, I use the adjacency list structure for graphs.
    // It is then the same as the search in the adjList and return the target id everytime.

    std::vector<BeaconID> path_outbeam(BeaconID id);

    // Non-compulsory operations

    // Estimate of performance:Theta(n)
    // Short rationale for estimate:Similar as get_name and coordinate, it is based on find beacons with operation giving next beacon to the current space and delete the last one space.

    bool remove_beacon(BeaconID id);

    // Estimate of performance:O(n²)
    // Short rationale for estimate:It is fisrt the same as the search in the adjList and return the source id everytime then neads to go through the edges to compare n times again to
    // return the longest beam and return id.
    std::vector<BeaconID> path_inbeam_longest(BeaconID id);

    // Estimate of performance:O(n)
    // Short rationale for estimate:Similar as get_color, but with searching on the adjList and do sum of the color everytime.

    Color total_color(BeaconID id);

    // Phase 2 operations

    // Estimate of performance:O(n)
    // Short rationale for estimate:Adding all the colors goes through the Adj
    std::vector<Coord> all_xpoints();

    // Estimate of performance:O(n)
    // Short rationale for estimate:The fib push and fibre struct push require not search and the only search occurs in adding resize of the fibre deleting repeated points.
    bool add_fibre(Coord xpoint1, Coord xpoint2, Cost cost);

    // Estimate of performance:O(n)
    // Short rationale for estimate:Getting the pair of coordinates and cost does takes complexity of O(n) while the twice added fibre is neccessary to make sure one point can be both on two ends of the fibre, making the whole structure undirected.
    std::vector<std::pair<Coord, Cost>> get_fibres_from(Coord xpoint);

    // Estimate of performance:O(nlogn)
    // Short rationale for estimate:The bubble sorting for fibs is combined with acustomed compare structure, according to the requirement of the task.
    std::vector<std::pair<Coord, Coord>> all_fibres();

    // Estimate of performance:O(nlogn)
    // Short rationale for estimate:Every fib pair is substituted by the next fib pair from the fibre required to be removed through checking both the ends of one fibre..
    bool remove_fibre(Coord xpoint1, Coord xpoint2);

    // Estimate of performance:O(n)
    // Short rationale for estimate: The whole list is passed through for clear and becuase the structure is linear, thus the complexity is n.
    void clear_fibres();

    // Estimate of performance: O(nlog(n))
    // Short rationale for estimate: Call the route_least_xpoints.
    std::vector<std::pair<Coord, Cost>> route_any(Coord fromxpoint, Coord toxpoint);

    // Non-compulsory operations
    // Estimate of performance: O(E)
    // Short rationale for estimate:  The nodes in fibres map and its fibres set are gone over for getting coords and cost using BFS.
    std::vector<std::pair<Coord, Cost>> route_least_xpoints(Coord fromxpoint, Coord toxpoint);

    // Estimate of performance: O(E)
    // Short rationale for estimate:The nodes in fibre maps and fibre sets are gone over for getting coords and cost using Dijktrast algorithms,updating the minimum cost dynamically.
    std::vector<std::pair<Coord, Cost>> route_fastest(Coord fromxpoint, Coord toxpoint);

    // Estimate of performance: O(nlog(n))
    // Short rationale for estimate: The cycle is checked through DFS. Thus, if the depth of the tree is large and the required two points are of difference with large levels, the performance will be bad.
    std::vector<Coord> route_fibre_cycle(Coord startxpoint);

    // Estimate of performance:  O(E)
    // Short rationale for estimate: If cycle is checked through Kruskal's MST, it will be trimed according to the cost by chossing minimum cost to generate two sets to be joined if there is no cycle.
    Cost trim_fibre_network();


private:
    // Add stuff needed for your class implementation here
    std::vector<BeaconID> brightness_increasing;
//    std::pair<BeaconID, BeaconData*> beaconlist_p;
    std::vector<BeaconID> IDlist;
//    std::vector<vector<BeaconID>> adjList;
    std::vector<BeaconData> Beaconlist;
    std::vector<std::vector<lightbeam>> Adj;

    std::map<Coord, std::map<Coord, std::shared_ptr<Fibre>>> Points;
    std::set<std::shared_ptr<Fibre>> fibres;
    std::vector<fib> fibs;
    std::vector<Coord> xPoints;
    std::queue<Coord> todo;
};


#endif // DATASTRUCTURES_HH
