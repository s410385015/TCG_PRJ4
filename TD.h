#pragma once
#include<iostream>
#include<string>
#include<vector>
#include <fstream>
#include"weight.h"
#include"board.h"



class TD{
    private:
        std::vector<vector<weight*>> weights;
    public:
        TD(){
        
        }
        ~TD(){}
    
        void add(weight* w){
            weights.push_back(w);
        }

        float estimate(const board& b)const{
            float value=0;
            
            for(weight* w: weights)
                value+=w->estimate(b);
            
            return value;
        }

        float update(const board& b,float u) const
        {
            float a=u/weights.size();
            float value=0;
            for(weight* w:weights)
                value+=w->update(b,a);
            
            return value;
        }

   

        void UpdateEpisode(std::vector<state>& path,float alpha=0.01)const
	    {
    
            float exact=0;
            for (path.pop_back(); path.size(); path.pop_back()) {
                state& move = path.back();
                float error = exact - (move.GetValue() - move.GetReward());
                exact = move.GetReward()+update(move.GetAfter(),alpha*error);
		    }
	    }

        void Save()
        {
            std::string name[4]={"w1.txt","w2.txt","w3.txt","w4.txt"};
            for(int i=0;i<(int)weights.size();i++)
            {
                std::ofstream out(name[i], std::ios::out | std::ios::binary | std::ios::trunc);
                out<<(*weights[i]);
            }
        }

        void Load()
        {
            std::string name[4]={"w1.txt","w2.txt","w3.txt","w4.txt"};
            int i=0;
            for(weight* w:weights)
            {
                std::ifstream in;
		        in.open(name[i++], std::ios::in | std::ios::binary);
                in>>*w;
                in.close();
            }
        }
};