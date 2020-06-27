#include<iostream>
#include<string>
#include<vector> 
#include<limits.h>
#include<queue>
using namespace std;

#define INF 15000 

struct point 
{ 
    float x,y;
};


vector<point>polygon;


bool onSegment(point p, point q, point r)             //  Given collinear and if q is present on segment pr then return true else false
 { 
    if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) && 
            q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y)) 
        return true; 
    return false; 
} 


int orientation(point p, point q, point r) 
{ 
    int val = (q.y - p.y) * (r.x - q.x) - 
              (q.x - p.x) * (r.y - q.y); 
  
    if (val == 0) return 0;                          // colinear 
    return (val > 0)? 1: 2;                          // clockwise(1) or counterclock wise(2) 
}


bool doIntersect(point p1, point q1, point p2, point q2) 
{ 
    // Find the four orientations needed for general and special cases
    int o1 = orientation(p1, q1, p2); 
    int o2 = orientation(p1, q1, q2); 
    int o3 = orientation(p2, q2, p1); 
    int o4 = orientation(p2, q2, q1); 
  
    // General case 
    if (o1 != o2 && o3 != o4) 
        return true; 
  
    // Special Cases 
    // p1, q1 and p2 are colinear and p2 lies on segment p1q1 
    if (o1 == 0 && onSegment(p1, p2, q1)) return true; 
  
    // p1, q1 and p2 are colinear and q2 lies on segment p1q1 
    if (o2 == 0 && onSegment(p1, q2, q1)) return true; 
  
    // p2, q2 and p1 are colinear and p1 lies on segment p2q2 
    if (o3 == 0 && onSegment(p2, p1, q2)) return true; 
  
     // p2, q2 and q1 are colinear and q1 lies on segment p2q2 
    if (o4 == 0 && onSegment(p2, q1, q2)) return true; 
  
    return false; // Doesn't fall in any of the above cases 
} 







bool check_inside(point sun){
    
    int size=polygon.size();
    point extreme={INF,sun.y};
    
    int count = 0, i = 0; 
    do
    { 
        int next = (i+1)%size; 
  

        if (doIntersect(polygon[i], polygon[next], sun, extreme)) 
        { 
            
            if (orientation(polygon[i], sun, polygon[next]) == 0)  // if colinear check on segment and return the result
               return onSegment(polygon[i], sun, polygon[next]); 
  
            count++; 
        } 
        i = next; 
    } while (i != 0); 
  
    // Return true if count is odd, false otherwise 
    return count&1;   
    
}




                        

int main(){ 
    
    point* p=new point();
    
    string s;                             //inputting co-ordinates of buildings
    cin.ignore();
    getline(cin,s);
    
    int size=s.length();
    
    int temp=0;
    string var;
    int i=0;
     
    while(i<size){
        if(s[i]!='[' && s[i]!=']' && s[i]!=',' && s[i]!=' '){ 
            
            if(s[i-1]=='['){
                temp=i;
                while(s[i]!=','){
                    i++;
                }
                var=s.substr(temp,i-temp);
                
                p->x=stof(var);
            }
            
            else if(s[i-1]==','){
                temp=i;
                while(s[i]!=']'){
                    i++;
                }
                var=s.substr(temp,i-temp);
                p->y=stof(var);
                point t={p->x,p->y};
                polygon.push_back(t);
            }
            
        }
        else i++;
    }
    
    
    getline(cin,s);             //inputting sun co-ordinates
     size=s.length();
     i=0;
     point sun;
    while(i<size){
        if(s[i]!='[' && s[i]!=']' && s[i]!=',' && s[i]!=' '){ 
            
            if(s[i-1]=='['){
                temp=i;
                while(s[i]!=','){
                    i++;
                }
                var=s.substr(temp,i-temp);
                
                p->x=stof(var);
            }
            
            else if(s[i-1]==','){
                temp=i;
                while(s[i]!=']'){
                    i++;
                }
                var=s.substr(temp,i-temp);
                p->y=stof(var);
                 sun={p->x,p->y};
            }
        }
        else i++;
        
    }
    
    check_inside(sun)? cout << "True \n": cout << "False \n"; ;
    
    
    
}
