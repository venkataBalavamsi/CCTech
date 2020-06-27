#include<iostream>
#include<string>
#include<vector> 
#include<limits.h>
#include<queue>
using namespace std;

typedef pair<float,int>pi;

struct point 
{ 
    float x,y;
};


vector<vector<point>>buildings;   // which stores co-ordinates of each building  and buildings[0] consists of co-ordinates of only first building
vector<point>rect;

priority_queue <pi, vector<pi>, greater<pi> > pq; // priority queue which is used in main calculation



point max_cordinates(int i){        // gives max x and max y co-ordinates of ith building
    float max_x=INT_MIN;
    float max_y=INT_MIN;
    for(int j=0;j<4;j++){
        if(buildings[i][j].x>max_x) max_x=buildings[i][j].x;
        if(buildings[i][j].y>max_y) max_y=buildings[i][j].y;
    }
    point temp={max_x,max_y};
    return temp;
}

point min_cordinates(int i){      // gives min x and min y co-ordinates of ith building
    float min_x=INT_MAX;
    float min_y=INT_MAX;
    for(int j=0;j<4;j++){
        if(buildings[i][j].x<min_x) min_x=buildings[i][j].x;
        if(buildings[i][j].y<min_y) min_y=buildings[i][j].y;
    }
    point temp={min_x,min_y};
    return temp;
}


float calculate_surface(point sun){    // function for calculating surface area exposed
    
    int size=buildings.size();
    
    for(int i=0;i<size;i++){
        pq.push(make_pair(max_cordinates(i).x,i));
    }
        
    float ans=0;   // final answer i.e length of the building exposed to sunlight
    
    while(!pq.empty()){
        
        int index=pq.top().second;
        if(pq.size()==size){                    // for first building only
            point maxi=max_cordinates(index);
            point mini=min_cordinates(index);
            ans=ans+maxi.x+maxi.y-mini.x-mini.y;
        }
        
        // line equation from  sun to max co-ordinates  is a1x + b1y = c1
        
        point maxi=max_cordinates(index);
        double a1 = maxi.y - sun.y; 
        double b1 = sun.x - maxi.x; 
        double c1 = a1*(sun.x) + b1*(sun.y);
        pq.pop();
        
        
     while(!pq.empty()){         //useful when 1st buiding completely shadow's 2nd building in that case we need to find intersection caused on 3rd building by 1st building     
         
        int next_index=pq.top().second;
        point maxi=max_cordinates(next_index);
        point mini=min_cordinates(next_index);
        
        if((a1*maxi.x+b1*maxi.y-c1) * (a1*mini.x+b1*mini.y-c1) <=0){   //intersects
             
             float temp=(a1*mini.x-c1)/-b1;
                         
            if(temp >mini.y && temp <maxi.y){           //intersects x=c line
                ans=ans+maxi.y-temp+maxi.x-mini.x;
            }
            
            else{                                       //intersects y=c line 
                ans=ans+maxi.x-(c1-b1*maxi.y)/a1;
            }
            
          break;
        }
        else pq.pop();
        
     }
        
       
        
    }
    return ans;

}

                     
                                

int main(){ 
    
    point* p=new point();
    
    string s;                             //inputting co-ordinates of buildings
    cin.ignore();
    getline(cin,s);
    
    int size=s.length();
    
    int temp=0;
    string var;
    int count=0;
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
                rect.push_back(t);
                count++;
            }
            
            if(count==4){
                count=0;
                buildings.push_back(rect);
                rect.clear();
                
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
    cout<<fixed<<calculate_surface(sun)<<endl;  
}



