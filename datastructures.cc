// Datastructures.cc

#include "datastructures.hh"

#include <random>

#include <cmath>
#include <algorithm>
#include <iostream>
#include <queue>
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

std::minstd_rand rand_engine; // Reasonably quick pseudo-random generator

template<typename Type>
Type random_in_range(Type start, Type end) {
    auto range = end - start;
    ++range;

    auto num = std::uniform_int_distribution<unsigned long int>(0, range - 1)(rand_engine);

    return static_cast<Type>(start + num);
}

// Modify the code below to implement the functionality of the class.
// Also remove comments from the parameter names when you implement
// an operation (Commenting out parameter name prevents compiler from
// warning about unused parameters on operations you haven't yet implemented.)

Datastructures::Datastructures() {
    Beaconlist = {};
    IDlist = {};
//    fibres = {};
    unsigned int AdjSize = 100;
    for (int i = 0; i < AdjSize; i++) {
        std::vector<lightbeam> column;
        for (int j = 0; j < AdjSize; j++) {
            lightbeam l;
            //l.NoI = NULL;
            column.push_back(l);
        }
        Adj.push_back(column);
    }
//    unsigned int AdjfibSize = 10000;
//    for (int i = 0; i< AdjfibSize; i++)
//    {
//        std::vector<fibre> fcolumn;
//        for (int j = 0; j< AdjfibSize; j++)
//        {
//            fibre f = {};
//            //l.NoI = NULL;
//            fcolumn.push_back(f);
//        }
//        Adjfibs.push_back(fcolumn);
//    }
}

Datastructures::~Datastructures() {
    clear_beacons();
}

int Datastructures::beacon_count() {
    // Replace this with your implementation
    return int(Beaconlist.size());
}

void Datastructures::clear_beacons() {
    Beaconlist.erase(Beaconlist.begin(), Beaconlist.end());
}

std::vector<BeaconID> Datastructures::all_beacons() {
    if (Beaconlist.empty()) return {NO_ID};
    // Replace this with your implementation
    return IDlist;
}

bool
Datastructures::add_beacon(BeaconID id/*id*/, const std::string &name/*name*/, Coord xy/*xy*/, Color color/*color*/) {
    auto ind = std::find(IDlist.begin(), IDlist.end(), id);
    unsigned int loc = ind - IDlist.begin();
    if (ind == IDlist.end()) {
        double brightness = 3 * color.r + 6 * color.g + color.b;
        BeaconData p;
        p.NoI = loc;
        p.name = name;
        p.id = id;
        p.src = {NO_ID};
        p.tgt = NO_ID;
        p.xy = xy;
        p.dist = 0;
        p.color = color;
//        Beacon *beacon;
//        beacon->beaconData = p;
        Beaconlist.push_back(p);
        IDlist.push_back(id);
        return true;
    }
    return false;
}

std::string Datastructures::get_name(BeaconID id/*id*/) {
    for (unsigned int i = 0; i < Beaconlist.size(); i++) {
        if (Beaconlist.at(i).id == id) return Beaconlist.at(i).name;
    }
    return NO_NAME;
}

Coord Datastructures::get_coordinates(BeaconID id/*id*/) {
    for (unsigned int i = 0; i < Beaconlist.size(); i++) {
        if (Beaconlist.at(i).id == id) return Beaconlist.at(i).xy;
    }
    return NO_COORD;
}

Color Datastructures::get_color(BeaconID id/*id*/) {
    for (unsigned int i = 0; i < Beaconlist.size(); i++) {
        if (Beaconlist.at(i).id == id) return Beaconlist.at(i).color;
    }
    return NO_COLOR;
}


std::vector<BeaconID> Datastructures::beacons_alphabetically() {
    std::sort(Beaconlist.begin(), Beaconlist.end(), [](BeaconData &p, BeaconData &q) { return p.name < q.name; });
    std::vector<std::vector<lightbeam>> temp;
    for (unsigned int i = 0; i < Beaconlist.size(); i++) {
//        unsigned int loc = Beaconlist.at(i).NoI;
        Beaconlist.at(i).NoI = i;
//        for (unsigned int j=0;j<Beaconlist.at(i).NoS.size();i++)
//        {
//            unsigned int locns;
//            temp[locns][i] = Adj[Beaconlist[i].NoS[j]][Beaconlist[i].NoI];
//        }
//        unsigned int locnt;
//        temp[locnt][i] = Adj[Beaconlist[i].NoT][Beaconlist[i].NoI];
        IDlist.push_back(Beaconlist.at(i).id);
    };
//    Adj = temp;
    return IDlist;
}

std::vector<BeaconID> Datastructures::beacons_brightness_increasing() {
    std::sort(Beaconlist.begin(), Beaconlist.end(),
              [](BeaconData &p, BeaconData &q) { return p.brightness < q.brightness; });
    std::vector<std::vector<lightbeam>> temp;
    for (unsigned int i = 0; i < Beaconlist.size(); i++) {
//        unsigned int loc = Beaconlist.at(i).NoI;
        Beaconlist.at(i).NoI = i;
//        for (unsigned int j=0;j<Beaconlist.at(i).NoS.size();i++)
//        {

//            unsigned int locns;
//            temp[locns][i] = Adj[Beaconlist[i].NoS[j]][Beaconlist[i].NoI];
//        }
//        unsigned int locnt;
//        temp[locnt][i] = Adj[Beaconlist[i].NoT][Beaconlist[i].NoI];
        brightness_increasing.push_back(Beaconlist.at(i).id);
    };
//    Adj = temp;
    IDlist = brightness_increasing;
    return brightness_increasing;
}

BeaconID Datastructures::min_brightness() {
    beacons_brightness_increasing();
    if (brightness_increasing.size()) return brightness_increasing[0];
    return NO_ID;
}

BeaconID Datastructures::max_brightness() {
    beacons_brightness_increasing();
    if (brightness_increasing.size()) return brightness_increasing.at(brightness_increasing.size() - 1);
    return NO_ID;
}

std::vector<BeaconID> Datastructures::find_beacons(std::string const &name/*name*/) {
    // Replace this with your implementation
    std::vector<BeaconID> IDs;
    for (unsigned int i = 0; i < Beaconlist.size(); i++) {
        if (Beaconlist.at(i).name == name) IDs.push_back(Beaconlist.at(i).id);
    }
    if (IDs.begin() != IDs.end()) return IDs;
    else
        return {NO_ID};
}

bool Datastructures::change_beacon_name(BeaconID id/*id*/, const std::string &newname/*newname*/) {
    // Replace this with your implementation
    for (unsigned int i = 0; i < Beaconlist.size(); i++) {
        if (Beaconlist.at(i).id == id) {
            Beaconlist.at(i).name = newname;
            return true;
        }
    }
    return false;
}

bool Datastructures::change_beacon_color(BeaconID id/*id*/, Color newcolor/*newcolor*/) {
    for (unsigned int i = 0; i < Beaconlist.size(); i++) {
        if (Beaconlist.at(i).id == id) {
            Beaconlist.at(i).color = newcolor;
            return true;
        }
    }
    return false;
}

bool Datastructures::add_lightbeam(BeaconID sourceid/*sourceid*/, BeaconID targetid/*targetid*/) {
    auto iters = std::find(IDlist.begin(), IDlist.end(), sourceid);
//    unsigned int loc = static_cast<unsigned int>(std::distance(ind,IDlist.begin()));
    unsigned int locs = static_cast<unsigned int>(iters - IDlist.begin());
    if (iters != IDlist.end()) {
        lightbeam beamt;
//        Beacons->beaconData.tgt = targetid;
        auto itert = std::find(IDlist.begin(), IDlist.end(), targetid);
        unsigned int loct = static_cast<unsigned int>(itert - IDlist.begin());
        beamt.NoI = Beaconlist[loct].NoI;
        beamt.NoS.push_back(locs);
//        Beacon* Beacont = Adj[loct][loct];
        beamt.color.r = (Beaconlist[locs].color.r + Beaconlist[loct].color.r) / 2;
        beamt.color.g = (Beaconlist[locs].color.g + Beaconlist[loct].color.g) / 2;
        beamt.color.b = (Beaconlist[locs].color.b + Beaconlist[loct].color.b) / 2;    //        Beacons->nxt = Beacont;
        beamt.dist = Beaconlist[locs].dist + 1;
        Beaconlist[loct].dist = Beaconlist[locs].dist + 1;
        Beaconlist[loct].NoS.push_back(locs);
        Beaconlist[loct].src.push_back(sourceid);
        Adj[loct][locs] = beamt;
//        Adj[loct][loct] = beamt;
        lightbeam beams;
        beams.NoI = Beaconlist[locs].NoI;
        beams.NoT = Beaconlist[loct].NoI;
        beams.dist = beamt.dist;
        Beaconlist[locs].tgt = targetid;
//        Beacon* Beacont = Adj[loct][loct];
        beams.color.r = (Beaconlist[locs].color.r + Beaconlist[loct].color.r) / 2;
        beams.color.g = (Beaconlist[locs].color.g + Beaconlist[loct].color.g) / 2;
        beams.color.b = (Beaconlist[locs].color.b + Beaconlist[loct].color.b) / 2;    //        Beacons->nxt = Beacont;
        Adj[locs][loct] = beams;
//        Adj[locs][locs] = beams;
//        Adj[loct][locs] = Beacont;
        return true;
    }

    return false;
}

std::vector<BeaconID> Datastructures::get_lightsources(BeaconID id/*id*/) {
    auto iter = std::find(IDlist.begin(), IDlist.end(), id);
    std::vector<BeaconID> IDs;
//    unsigned int loc = static_cast<unsigned int>(std::distance(ind,IDlist.begin()));
    unsigned int loc = static_cast<unsigned int>(iter - IDlist.begin());
    if (iter != IDlist.end()) {
        for (unsigned int i = 0; i < IDlist.size(); i++) {
            if (Adj[i][loc].NoT == Adj[loc][i].NoI)
                IDs.push_back(IDlist[i]);
        }
        return IDs;
    }
    return {NO_ID}; // Replace with actual implementation

}

std::vector<BeaconID> Datastructures::path_outbeam(BeaconID id/*id*/) {
    std::vector<BeaconID> IDs;
    auto ind = std::find(IDlist.begin(), IDlist.end(), id);
//    //    unsigned int loc = static_cast<unsigned int>(std::distance(ind,IDlist.begin()));
    unsigned int loc = static_cast<unsigned int>(ind - IDlist.begin());
    if ((ind == IDlist.end()) || Beaconlist.empty() || Adj[loc].empty()) return {NO_ID};
    unsigned int i = 0;
    while (i < Beaconlist.size()) {
        if (Adj[loc][i].NoT == Adj[i][loc].NoI) {
            IDs.push_back(Beaconlist[loc].id);
            IDs.push_back(Beaconlist[loc].tgt);
            loc = i;
            i = 0;
        } else i++;

    }
    return IDs;
}

bool Datastructures::remove_beacon(BeaconID id/*id*/) {
    // Replace this with your implementation
    auto ind = std::find(IDlist.begin(), IDlist.end(), id);
//    unsigned int loc = static_cast<unsigned int>(std::distance(ind,IDlist.begin()));
    unsigned int loc = static_cast<unsigned int>(ind - IDlist.begin());
//    //    unsigned int count = IDlist_.size()-loc;
    if (ind != IDlist.end()) {
        unsigned int s = Beaconlist.size();
        for (unsigned int i = loc; i < s; i++) {
            Beaconlist[loc] = Beaconlist[loc + 1];
            IDlist[loc] = IDlist[loc + 1];
            Adj[loc].erase(Adj[loc].begin(), Adj[loc].end());
            for (unsigned int j = 0; j < Beaconlist.size(); j++) {
                if (Adj[j][loc].NoT == Adj[loc][j].NoI) Adj[j].erase(Adj[j].begin() + loc);
            }
        }
        if (Beaconlist.size() == s)
            Beaconlist.erase(Beaconlist.begin() + s);
        return true;
    }
    return false;
}

std::vector<BeaconID> Datastructures::path_inbeam_longest(BeaconID id/*id*/) {
    // Replace this with your implementation
    auto ind = std::find(IDlist.begin(), IDlist.end(), id);
//    unsigned int loc = static_cast<unsigned int>(std::distance(ind,IDlist.begin()));
    unsigned int loc = static_cast<unsigned int>(ind - IDlist.begin());
    if (ind == IDlist.end() || Beaconlist.empty() || Beaconlist[loc].dist == 0) return {NO_ID};
    std::vector<BeaconID> IDs;
    IDs.push_back(Beaconlist[loc].id);
    int d = Beaconlist[loc].dist;
    while ((d != 0) && (loc != IDlist.size())) {
        for (unsigned int i = 0; i < Beaconlist[loc].NoS.size(); i++) {
            if (Beaconlist[loc].NoS.size() == 1) {
                loc = Beaconlist[loc].NoS[0];
                d = Beaconlist[loc].dist;
            } else if (Beaconlist[loc].NoS.size() > 1) {
                if (Beaconlist[Beaconlist[loc].NoS[i]].dist < Beaconlist[Beaconlist[loc].NoS[i + 1]].dist) {
                    d = Beaconlist[Beaconlist[loc].NoS[i + 1]].dist;
                    loc = i + 1;
                }
            }
            IDs.push_back(Beaconlist[loc].id);
        }


//        unsigned int count = Beaconlist[loc][loc]->No.size();
//        unsigned int lc = count;
//        while(count != 0)
//        {
//            if(Beaconlist[loc][Beaconlist[loc][loc]->No[lc]]->dist > Beaconlist[loc][Beaconlist[loc][loc]->No[count-1]]->dist)  lc = count-1;
//            count --;
//        }
//        d = Beaconlist[loc][Beaconlist[loc][loc]->No[lc]]->dist;
//        loc = Beaconlist[loc][loc]->No[lc];
    }
    return IDs;
}

Color Datastructures::total_color(BeaconID id/*id*/) {
    auto ind = std::find(IDlist.begin(), IDlist.end(), id);
    unsigned int loc = static_cast<unsigned int>(ind - IDlist.begin());
//    unsigned int loc = static_cast<unsigned int>(std::distance(ind,IDlist.begin()));
    if (ind == IDlist.end() || Beaconlist.empty() || Adj[loc].empty()) return {NO_COLOR};
    std::vector<BeaconID> IDs;
    Color totalcolor;
    totalcolor.r = Beaconlist[loc].color.r;
    totalcolor.g = Beaconlist[loc].color.g;
    totalcolor.b = Beaconlist[loc].color.b;
    int count = 1;
    while (!Beaconlist[loc].NoT) {
//        loc = static_cast<unsigned int>(std::distance(ind,IDlist.begin()));
        totalcolor.r += Beaconlist[Beaconlist[loc].NoT].color.r;
        totalcolor.g += Beaconlist[Beaconlist[loc].NoT].color.g;
        totalcolor.b += Beaconlist[Beaconlist[loc].NoT].color.b;
        loc = Beaconlist[loc].NoT;
        count++;
    }
    totalcolor.r /= count;
    totalcolor.g /= count;
    totalcolor.b /= count;
    return totalcolor;
}

std::vector<Coord> Datastructures::all_xpoints() {
    // Replace this with your implementation
    auto it = std::unique(xPoints.begin(), xPoints.end());
    xPoints.resize(std::distance(xPoints.begin(), it));
    return xPoints;
}

bool Datastructures::add_fibre(Coord xpoint1, Coord xpoint2, Cost cost) {
    // Replace this with your implementation
//    if (xpoint1 != xpoint2)
//    {
//        auto ft = Points.find(xpoint1);
//        auto sd = Points.find(xpoint2);
//        if (ft == Points.end())
//        {
//            if (sd == Points.end())
//            {
//                return false;
//            }
//            else
//            {
//                // Add fibre2
//                auto fibre2 = std::make_shared<struct Fibre>(Fibre{xpoint2, xpoint1, cost});
//                std::map <Coord, std::shared_ptr<struct Fibre>>f2;
//                f2.insert({xpoint1, fibre2});
//                Points.insert({xpoint2,f2});
//                fibres.insert({fibre2});
//                fibs.push_back(std::make_pair(xpoint2, xpoint1));

//                // Add fibre1
//                auto fibre = std::make_shared<Fibre>(Fibre{xpoint1, xpoint2, cost});
////                struct Fibre fibre = {xpoint2, xpoint1, cost};
//                xPoints.push_back(xpoint1);
//                xPoints.push_back(xpoint2);

//                std::map <Coord, std::shared_ptr<struct Fibre>>f;
//                f.insert({xpoint2, fibre});
//                Points.insert({xpoint1,f});
//                fibres.insert({fibre});
//                fibs.push_back(std::make_pair(xpoint1, xpoint2));

//            }
//        }
//        else
//        {
//            if (sd == Points.end())
//            {
//                auto fibre = std::make_shared<Fibre>(Fibre{xpoint1, xpoint2, cost});
//                xPoints.push_back(xpoint2);
//                xPoints.push_back(xpoint1);
//                std::map <Coord, std::shared_ptr<struct Fibre>>f;
//                f.insert({xpoint2, fibre});
//                Points.insert({xpoint1,f});
//                fibres.insert({fibre});
//                fibs.push_back(std::make_pair(xpoint1, xpoint2));

//                auto fibre2 = std::make_shared<Fibre>(Fibre{xpoint2, xpoint1, cost});
//                std::map <Coord, std::shared_ptr<struct Fibre>>f2;
//                f2.insert({xpoint1, fibre2});
//                Points.insert({xpoint2,f2});
//                fibres.insert({fibre2});
//                fibs.push_back(std::make_pair(xpoint2, xpoint1));
//            }
//            else
//            {
////                if (Points.find(xpoint1)->second.first == Points.find(xpoint2)->second.second)
////                    return false;
//                auto fibre = std::make_shared<Fibre>(Fibre{xpoint1, xpoint2, cost});
//                std::map <Coord, std::shared_ptr<struct Fibre>>f;
//                f.insert({xpoint2, fibre});
//                Points.insert({xpoint2, f});
//                fibres.insert({fibre});
//                fibs.push_back(std::make_pair(xpoint1, xpoint2));

//                auto fibre2 = std::make_shared<Fibre>(Fibre{xpoint2, xpoint1, cost});
//                std::map <Coord, std::shared_ptr<struct Fibre>>f2;
//                f2.insert({xpoint1, fibre2});
//                Points.insert({xpoint1, f2});
//                fibres.insert({fibre2});
//                fibs.push_back(std::make_pair(xpoint2, xpoint1));
//            }
//        }
//        return true;
//    }
//    return false;
    if (xpoint1 != xpoint2)
    {
        auto fibre = std::make_shared<Fibre>(Fibre{xpoint1, xpoint2, cost});

        // Check xpoint1
        auto ft = Points.find(xpoint1);
        if (ft != Points.end()) {
            auto sd = ft->second.find(xpoint2);
            if (sd != ft->second.end()) return false;
            else ft->second.insert({xpoint2, fibre});
            fibs.push_back(fib(xpoint2, xpoint1));

        }
        else
        {
            // Add fibre
            xPoints.push_back(xpoint1);
            std::map<Coord, std::shared_ptr<Fibre>> temp;
            temp.insert({xpoint2, fibre});
            Points.insert({xpoint1, temp});
            fibs.push_back(fib(xpoint1, xpoint2));
          }

        // Check xpoint2
        auto sd = Points.find(xpoint2);
        if (sd != Points.end())
        {
            auto it2 = sd->second.find(xpoint1);
            if (it2 != sd->second.end()) return false;
            else sd->second.insert({xpoint1, fibre});
            fibs.push_back(fib(xpoint1, xpoint2));
        }
        else
        {
            // Add fibre
            xPoints.push_back(xpoint2);
            std::map<Coord, std::shared_ptr<Fibre>> temp;
            temp.insert({xpoint1, fibre});
            Points.insert({xpoint2, temp});
            fibs.push_back(fib(xpoint2, xpoint1));
        }
        fibres.insert(fibre);
        return true;
    }
    return false;
}

std::vector<std::pair<Coord, Cost>> Datastructures::get_fibres_from(Coord xpoint) {
    // Replace this with your implementation
    std::vector<std::pair<Coord, Cost>> route;

    auto it = Points.find(xpoint);
    if (it != Points.end()) {
        for (auto f : it->second) {
            std::pair<Coord, Cost> temp(f.first, f.second->cost);
            route.push_back(temp);
        }
    }

    return route;
}

std::vector<std::pair<Coord, Coord> > Datastructures::all_fibres() {
    // Replace this with your implementation
    std::sort(fibs.begin(), fibs.end(), fib_comp());
//        {return p < q;});
//    std::sort(fibres.begin(), fibres.end(), fibre_comp());
//              [](Fibre *p, Fibre *q)
//        {return p < q;});

//    fib f;
//    for(unsigned int i = 0; i< fibs.size()-1;i++)
//        for(unsigned int j = i+1; j< fibs.size();j++)
//            if (fibs.at(i).first > fibs.at(j).first)
//            {
//                f = fibs.at(i);
//                fibs.at(i) = fibs.at(j);
//                fibs.at(j) = f;
//            }
//            else if(fibs.at(i).first == fibs.at(j).first)
//                if (fibs.at(i).second > fibs.at(j).second)
//                {
//                    f = fibs.at(i);
//                    fibs.at(i) = fibs.at(j);
//                    fibs.at(j) = f;
//                }

//    return fibs;

//    std::set<std::shared_ptr<Fibre>> fibres;
//    for (auto xpoint : xPoints)
//    {
//       auto it = Points.find(xpoint);
//       for (auto f : it->second)
//       {
//          auto tmp = fibres.find(f.second);
//           if (tmp == fibres.end())
//           {
//               fibres.insert(f.second);
//           }
//        }
//    }


    // somewhere at your callside

//    std::sort(fibs.begin(), fibs.end());
    return fibs;
//    return fibs;
}

bool Datastructures::remove_fibre(Coord xpoint1, Coord xpoint2) {
    // Replace this with your implementation
    bool removed = false;

    auto ft = Points.find(xpoint1);
    if (ft != Points.end())
    {
        auto it1 = ft->second.find(xpoint2);
        if (it1 != ft->second.end())
        {
            fibres.erase(it1->second);
            ft->second.erase(it1);
            removed = true;
        }
        if (ft->second.size() == 0)
        {
            Points.erase(ft);
        }
    }

    if (removed)
    {
        auto sd = Points.find(xpoint2);
        if (sd != Points.end())
        {
            auto it2 = sd->second.find(xpoint1);
            if (it2 != sd->second.end()) {
                sd->second.erase(it2);
            }
            if (sd->second.size() == 0) {
                Points.erase(sd);
            }
        }
    }

    return removed;
//    return false;
}

void Datastructures::clear_fibres() {
    // Replace this with your implementation
    xPoints.clear();
    fibs.clear();
    fibres.clear();

//    unordered_xpoints.clear();
//    ordered_xpoints.clear();
//    fibres.clear();
}

std::vector<std::pair<Coord, Cost>> Datastructures::route_any(Coord fromxpoint, Coord toxpoint) {
    // Replace this with your implementation
    return route_least_xpoints(fromxpoint, toxpoint);
}

std::vector<std::pair<Coord, Cost>> Datastructures::route_least_xpoints(Coord fromxpoint, Coord toxpoint) {
    // Replace this with your implementation
    std::vector<std::pair<Coord, Cost>> route;
//    std::queue<Coord> todo;
    bool stop = false;

    // BFS
    auto ft = Points.find(fromxpoint);
    auto sd = Points.find(toxpoint);
    if (ft != Points.end() && sd != Points.end()) {
        std::map<Coord, std::pair<Cost, Coord>> route_cost;
        route_cost.insert({fromxpoint, std::make_pair(0, fromxpoint)});

        todo.push(fromxpoint);

        while (!todo.empty())
        {
            auto iter = Points.find(todo.front());
            auto cost = route_cost.find(todo.front())->second.first;

            for (auto f : iter->second) {
                auto i = route_cost.find(f.first);
                if (i == route_cost.end())
                {
                    route_cost.insert({f.first, std::make_pair(cost + f.second->cost, todo.front())});
                    todo.push(f.first);
                }
                if (f.first == toxpoint) {
                    stop = true;
                    break;
                }
            }

            if (stop) {
                break;
            }
            todo.pop();
        }

        if (stop)
        { // route exists
            std::vector<std::pair<Coord, Cost>> rev_route;
            auto it = route_cost.find(toxpoint);

            rev_route.push_back(std::make_pair(toxpoint, it->second.first));
            while (it->second.second != fromxpoint) {
                it = route_cost.find(it->second.second);
                rev_route.push_back(std::make_pair(it->first, it->second.first));
            }
            rev_route.push_back(std::make_pair(fromxpoint, 0));
            route.insert(route.end(), rev_route.rbegin(), rev_route.rend());
        }
    }

    return route;
//    return {};
}

std::vector<std::pair<Coord, Cost>> Datastructures::route_fastest(Coord fromxpoint, Coord toxpoint) {
    // Replace this with your implementation
//    std::queue<Xpoint> todo;
    std::vector<std::pair<Coord, Cost>> route;

    // Dijkstra
    auto ft = Points.find(fromxpoint);
    auto sd = Points.find(toxpoint);
    if (ft != Points.end() && sd != Points.end()) {
        std::set<std::shared_ptr<Fibre>> edges; // visited edges
        std::map<Coord, Xpoint *> route_cost;

        auto comp = [](Xpoint *a, Xpoint *b) { return a->total > b->total; };
        std::priority_queue<Xpoint *, std::vector<Xpoint *>, decltype(comp)> queue(comp);

        Xpoint *temp = (struct Xpoint *) malloc(sizeof(struct Xpoint));
        temp->point = fromxpoint;
        temp->prev = fromxpoint;
        temp->total = 0;
        route_cost.insert({fromxpoint, temp});
        queue.push(temp);

        while (!queue.empty()) {
            queue.pop();

//            // Neighbors
            auto nb = Points.find(queue.top()->point);
            auto previous = nb->first;
            auto prev_cost = queue.top()->total;
            for (auto f : nb->second) {
                Coord nb_coord = f.first;
                auto edge = f.second;
                Cost cost = edge->cost;

                auto edge_visited = edges.find(edge);
                if (edge_visited != edges.end()) continue;
                else edges.insert(edge);

                auto tmp = route_cost.find(nb_coord);
                if (tmp == route_cost.end()) {
                    Xpoint *nb_xpoint = (struct Xpoint *) malloc(sizeof(struct Xpoint));
                    nb_xpoint->point = nb_coord;
                    nb_xpoint->prev = previous;
                    nb_xpoint->total = prev_cost + cost;
                    route_cost.insert({nb_coord, nb_xpoint});
                    queue.push(nb_xpoint);
                }
                else {
                    // Update neighbor's cost
                    Xpoint *nb_xpoint = (tmp->second);
                    if (nb_xpoint->total > prev_cost + cost)
                    {
                        nb_xpoint->prev = previous;
                        nb_xpoint->total = prev_cost + cost;
                    }
                }
            }
        }

        auto it2 = route_cost.find(toxpoint);
        if (it2 != route_cost.end()) { // route exists
            std::vector<std::pair<Coord, Cost>> rev_route;

            rev_route.push_back(std::make_pair(toxpoint, it2->second->total));
            while (it2->second->prev != fromxpoint) {
                it2 = route_cost.find(it2->second->prev);
                rev_route.push_back(std::make_pair(it2->first, it2->second->total));
            }
            rev_route.push_back(std::make_pair(fromxpoint, 0));

            route.insert(route.end(), rev_route.rbegin(), rev_route.rend());
        }
    }

    return route;
//    return {};
}

std::vector<Coord> Datastructures::route_fibre_cycle(Coord startxpoint) {
    // Replace this with your implementation
    std::vector<Coord> cycle;
    bool stop = false;
    //DFS
    auto it = std::find(xPoints.begin(), xPoints.end(), startxpoint);
    if (it != xPoints.end())
    {
        std::set<Coord> isVisited; // visited xpoints
        isVisited.insert(startxpoint);
        std::set<std::shared_ptr<Fibre>> edges; // visited edges

        cycle.push_back(startxpoint);

        while (!cycle.empty())
        {
            auto nb = Points.find(cycle.back());
            int nb_neighbors = nb->second.size();
            int count = 0;

            for (auto f : nb->second) {
                auto edge = f.second;
                auto edge_visited = edges.find(edge);
                if (edge_visited == edges.end()) { // not visited
                    edges.insert(edge);

                    auto neighbor = f.first;
                    cycle.push_back(neighbor);

                    auto point_visited = isVisited.find(neighbor);
                    if (point_visited != isVisited.end())
                    { // cycle
                        stop = true;
                        break;
                    }
                    isVisited.insert(neighbor);
                    break;
                }
                count++;
            }

            if (stop) break;
            if (count == nb_neighbors) {
                cycle.pop_back();
            }
        }
    }

    return cycle;
//    return {};
}

Cost Datastructures::trim_fibre_network() {
    // Replace this with your implementation
    //kruskal's MST
//    Cost total = NO_COST;

//    if (!fibres.empty()) {
//        total = 0;

//        // Edges
//        auto comp = [](std::shared_ptr<Fibre> p, std::shared_ptr<Fibre> q) { return p->cost > q->cost; };
//        std::priority_queue<std::shared_ptr<Fibre>, std::vector<std::shared_ptr<Fibre>>, decltype(comp)> edges(comp);
//        for (auto edge : fibres) {
//            edges.push(edge);
//        }
//        fibres.clear();

//        // Vertices
//        std::map<Coord, std::shared_ptr<std::set<Coord>>> vertices;
//        for (auto vertex : Points) {
////            std::make_shared<std::set<Coord>> temp = ;
//            vertices.insert(vertex,std::shared_ptr<std::set<Coord>>{vertex});
//        }

//        while (!edges.empty()) {
//            auto edge = edges.top();
//            edges.pop();

//            auto subset1 = vertices.at(edge->xpoint1);
//            auto subset2 = vertices.at(edge->xpoint2);
//            bool flag1 = (*subset1).find(edge->xpoint2) == (*subset1).end();
//            bool flag2 = (*subset2).find(edge->xpoint1) == (*subset2).end();
//            if (flag1 && flag2) { // Disjoint sets when no cycle
//                fibres.insert(edge);
//                total = total + edge->cost;

//                (*subset1).insert((*subset2).begin(), (*subset2).end());
//                for (auto i : *subset2) {
//                    vertices.erase(i);
//                    vertices.insert({i, subset1});
//                }
//            }
//            else
//            { // trim
//                remove_fibre(edge->xpoint1, edge->xpoint2); // Remove fibre
//            }
//        }
//    }
//    return total;
}
