/**
 * DBSCAN:
 * 
 * Find the points in the ε (eps) neighborhood of every point, and identify the core 
 * points with more than minPts neighbors.
 * 
 * Find the connected components of core points on the neighbor graph, ignoring all 
 * non-core points.
 * 
 * Assign each non-core point to a nearby cluster if the cluster is an ε (eps) neighbor, 
 * otherwise assign it to noise.
 * 
 */

#include "City.hpp"
#include "Heap.hpp"
#include "JsonFacade.hpp"
#include "json.hpp"
#include "GeoJson.hpp"
#include <iostream>
#include <string>
#include <vector>

struct Cluster {
    vector<City *> points;
    int size;
    double eps;
    //center ??
    Cluster(double e) {
        size = 0;
        eps = e;
    }

    void AddPoint(City *c) {
        size++;
        points.push_back(c);
    }

    int Size() {
        return points.size();
    }

    bool InNeighborhood(City *p) {
        double d;
        for (int i = 0; i < points.size(); i++) {
            d = p->Distance(points[i]->lat, points[i]->lon);
            // your not me
            if (p->lat == points[i]->lat && p->lon == points[i]->lon) {
                continue;
            }

            // close to me, then your in.
            if (d <= eps && !p->visited) {
                AddPoint(p);
                return true;
            }
        }
        return false;
    }
};

class Dbscan {
private:
    vector<City *> Cities;
    int minPoints;
    double eps;
    vector<Cluster *> Clusters;
    Heap<City> *H;
    string objectId; // its a number but a string for json reasons

    /**
     * Description:
     *     This function gets a filename and a state. It loads
     *     a vector of city pointers and returns it. 
     * Depends on:
     *     json.hpp
     *     City.hpp
     * Params:
     *     string filename : json file to open 
     *     string state : name of us state to filter by
     * 
     * Returns:
     *     vector of city pointers. 
     */
    void LoadCities(string filename, string state = "") {
        json obj;
        JsonFacade J(filename);

        // loads an array of cities from specified state
        for (int i = 0, id = 0; i < J.getSize(); i++) {
            obj = J.getNext();

            if (obj["state"] == state || state == "") {
                Cities.push_back(new City(obj, id));
                id++;
            }
        }
    }

    void LoadHeap(int city_id) {
        H->Clear();
        double lat = Cities[city_id]->lat;
        double lon = Cities[city_id]->lon;
        for (int j = 0; j < Cities.size(); j++) {
            Cities[j]->priority = Cities[j]->Distance(lat, lon);
            H->Insert(Cities[j]);
        }
    }

public:
    Dbscan(string filename, int mp, double d) {
        LoadCities(filename);
        objectId = "0";
        minPoints = mp;
        eps = d;
        H = new Heap<City>(false);
        findClusters();
    }

    int inCluster(City *c) {
        for (int i = 0; i < Clusters.size(); i++) {
            if (Clusters[i]->InNeighborhood(c)) {
                return i;
            }
        }
        return -1;
    }

    void findClusters() {
        int processedCities = 0;
        int cityId = rand() % Cities.size();
        double lat, lon, distance;
        int clusterSize = 0;
        int index;
        bool added;
        Cluster *c;

        // new empty cluster
        c = new Cluster(eps);
        c->AddPoint(Cities[0]);
        Cities[0]->visited = true;
        Clusters.push_back(c);

        for (int j = 0; j < Cities.size(); j++) {
            for (int c = 0; c < Clusters.size(); c++) {
                added = Clusters[c]->InNeighborhood(Cities[j]);
                if (added) {
                    Cities[j]->visited = true;
                    break;
                }
            }
            if (!added) {
                c = new Cluster(eps);
                c->AddPoint(Cities[j]);
                Clusters.push_back(c);
                cout << Clusters.size() << endl;
            }
        }
        cout<<endl;
        for (int c = 0; c < Clusters.size(); c++) {
            cout << Clusters[c]->points.size() << endl;
        }
    }

    void MakeGeoJson(){
        GeoJson GJ;
        json obj = json::array();
        City* c;
        double lat,lon;

        for (int i = 0; i < Clusters.size(); i++) {
            if(Clusters[i]->points.size() >= minPoints){
                obj = json::array();
                c = Clusters[i]->points[0];
                for(int j=0;j<Clusters[i]->points.size();j++){
                    c = Clusters[i]->points[j];
                    lat = c->lat;
                    lon = c->lon;
                    obj.push_back({lon,lat});
                    
                }
                c = Clusters[i]->points[0];
                lat = c->lat;
                lon = c->lon;
                obj.push_back({lon,lat});
                //GJ.AddPolygon(obj);
                GJ.AddGeoPoint()
            }
        }
        GJ.PrintJson("clusters.geojson");

    }
};