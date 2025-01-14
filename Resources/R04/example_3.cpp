/**
 * Example 3
 * This is an example of how to add a polygon to a geojson object 
 * It uses the previous two examples.
 * 
 */ 

#include <fstream>
#include <iostream>
#include <string>
#include "json.hpp"            
#include "GeoJson.hpp"
#include "HexColors.hpp"

using json = nlohmann::json;    

using namespace std;


int main(int argc, char **argv) {

    /// FROM PRIVIOUS EXAMPLES
    GeoJson GJ;
    HexColors Hex;

    double wichita_falls_latitude = 33.9137085;
    double wichita_falls_longitude = -98.4933873;

    double dallas_latitude = 32.7766642;
    double dallas_longitude = -96.7969878999;

    double norman_latitude = 35.2225668;
    double norman_longitude = -97.4394777;


    // The returned id is so we can reference the point in the object and add
    // colors etc to that geojson feature
    int id1 = GJ.AddGeoPoint(wichita_falls_longitude,wichita_falls_latitude);

    // Change the marker color for this marker using hex green
    GJ.AddProperty(id1,"marker-color","#00FF00");
    GJ.AddProperty(id1,"name","Wichita Falls");


    // We added a point for wichita falls, now lets add dallas
    int id2 = GJ.AddGeoPoint(dallas_longitude,dallas_latitude);

    // Change the marker color for this marker using a random color
    GJ.AddProperty(id2,"marker-color",Hex.GetRandomColor());  
    GJ.AddProperty(id2,"name","Dallas");

    // We added 1 more point for norman
    int id3 = GJ.AddGeoPoint(norman_longitude,norman_latitude);

    // Change the marker color for this marker using a random color
    GJ.AddProperty(id3,"marker-color",Hex.GetRandomColor());  
    GJ.AddProperty(id3,"name","Dallas");


    // First way to make a line using a json array (like a vector)
    json line1 = json::array();

    // Push two points onto our json array
    line1.push_back({wichita_falls_longitude,wichita_falls_latitude});
    line1.push_back({dallas_longitude,dallas_latitude});

    // Add the json array to our geojson class turning it into a "linestring"
    int id4 = GJ.AddLineString(line1);

    // Change the properties of the lines color and give it a name.
    GJ.AddProperty(id4,"stroke",Hex.GetRandomColor());
    GJ.AddProperty(id4,"name","Wichita Falls to Dallas");

    // Create a json object
    json line2 = json::object();

    // Add multiple points to our json object / line.
    line2 = {{dallas_longitude,dallas_latitude},{norman_longitude,norman_latitude}};

    // Insert our json into the geojson class turning it into a "linestring"
    int id5 = GJ.AddLineString(line2);
    GJ.AddProperties(id5,{{"name","Dallas to Norman"},{"stroke","#FF0000"},{"stroke-opacity", "0.8"},{ "stroke-width","3"}});
               

    // Lets reuse the line2 object to add a third line connecting the triangle.
    line2 = {{norman_longitude,norman_latitude},{wichita_falls_longitude,wichita_falls_latitude}};

    // Insert our json into the geojson class turning it into a "linestring"
    int id6 = GJ.AddLineString(line2);
    GJ.AddProperties(id6,{{"name","Dallas to Norman"},{"stroke",Hex.GetRandomColor()},{"stroke-opacity", "0.8"},{ "stroke-width","4"}});
               

    ///// END PREVIOUS EXAMPLES


    json polygon1 = json::array();

    polygon1.push_back({wichita_falls_longitude,wichita_falls_latitude});
    polygon1.push_back({dallas_longitude,dallas_latitude});
    polygon1.push_back({norman_longitude,norman_latitude});
    polygon1.push_back({wichita_falls_longitude,wichita_falls_latitude});

    int id7 = GJ.AddPolygon(polygon1);
    GJ.AddProperties(id7,{
            {"name","Home Town Area"},
            {"stroke",Hex.GetRandomColor()},
            {"stroke-opacity", "0.8"},
            { "stroke-width","2"},
            {"fill",Hex.GetRandomColor()},
            {"fill-opacity","0.5"}
            });


    // Print the geojson to an output file
    GJ.PrintJson("example_3.geojson");

}