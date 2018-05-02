#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <set>
#include <math.h>
#include <ctime>
using namespace std;

class State {
    public:
        vector<vector<int>> game_state;
        int w, h, depth =0, state_cost =0;
        vector<string> action;
        State() {}
        State(vector<vector<int>> game_state, int depth, int state_cost, vector<string> action) {
            this->game_state = game_state;
            this->depth = depth;
            this->state_cost = state_cost;
            this->action = action;
        }

        vector<vector<int>> getGameState() {
            return game_state;
        }

        void setGameState(vector<vector<int>> game_state) {
            this->game_state = game_state;
        }

        int getDepth() {
            return depth;
        }

        void setDepth(int depth) {
            this->depth = depth;
        }

        int getStateCost() {
            return state_cost;
        }

        void setStateCost(int state_cost) {
            this->state_cost = state_cost;
        }

        vector<string> getAction() {
            return action;
        }

        void setAction(vector<string> action) {
            this->action = action;
        }

        bool isComplete() {
            int flag=0;
            for(int i=0;i<game_state.size();i++)
            {
                for(int j=0;j<game_state[0].size();j++)
                {
                    if(game_state[i][j]==-1)
                    {
                        flag=1;
                    }
                }
            }
            if(flag==1)
                return false;
            else
                return true;
        }
        void display() {
            cout << game_state[0].size() << "," << game_state.size() << "," << endl;
            for(int i=0 ; i<game_state.size() ; i++) {
                for(int j=0 ; j<game_state[0].size() ; j++) {
                    cout<<game_state[i][j]<<",";
                }
                cout<<"\n";
            }
            cout << endl;
        }
        void normalize(){
            int nextIdx = 3;
            for(int i = 0;i < game_state.size();i++) {
                for(int j = 0;j < game_state[0].size();j++) {
                    if (game_state[i][j]==nextIdx) {
                    nextIdx++;
                    } else if (game_state[i][j] > nextIdx) { swapIdx(nextIdx,game_state[i][j]); nextIdx++;
                    }
                }
            }
        }

        void swapIdx(int idx1,int idx2) {
            for(int i = 0;i < game_state.size();i++) {
                for(int j = 0;j < game_state[0].size();j++) {
                    if (game_state[i][j]==idx1) {
                        game_state[i][j]=idx2;
                    } else if (game_state[i][j]==idx2){
                        game_state[i][j]=idx1;
                    }
                }
            }
        }
};

class Tile {
public:
    int tile_id, x1, y1, x2, y2;
    int dir[4] = {0, 0, 0, 0};      // ->  {up, down, left, right}

    bool checkMoveUp(State state){
        int id=this->y1;
        if(this->tile_id==2){
            while(id<=this->y2)
            {
                if(state.game_state[this->x1-1][id]==-1)
                {
                    ++id;
                }else{
                    break;
                }
            }
            if(id>this->y2){
                return true;
            }
        }

        for(id=this->y1;id<=this->y2;id++)
        {
            if(state.game_state[this->x1-1][id]!=0)
            {
                return false;
                break;
            }
        }
        return true;
    }
    bool checkMoveDown(State state) {
        int id=this->y1;
        if(this->tile_id==2){
            while(id<=this->y2)
            {
                if(state.game_state[this->x2+1][id]==-1)
                {
                    ++id;
                }else{
                    break;
                }
            }
            if(id>this->y2){
                return true;
            }
        }
        for(id=this->y1;id<=this->y2;id++)
        {
            if(state.game_state[this->x2+1][id]!=0)
            {
                return false;
                break;
            }
        }
        return true;
    }
    bool checkMoveLeft(State state) {
        int id=this->x1;
        if(this->tile_id==2){
            while(id<=this->x2)
            {
                if(state.game_state[id][this->y1-1]==-1)
                {
                    ++id;
                }else{
                    break;
                }
            }
            if(id>this->x2){
                return true;
            }
        }
        for(id=this->x1;id<=this->x2;id++)
        {
            if(state.game_state[id][this->y1-1]!=0)
            {
                return false;
                break;
            }
        }
        return true;
    }
    bool checkMoveRight(State state) {
        int id=this->x1;
        if(this->tile_id==2){
            while(id<=this->x2)
            {
                if(state.game_state[id][this->y2+1]==-1)
                {
                    ++id;
                }else{
                    break;
                }
            }
            if(id>this->x2){
                return true;
            }
        }
        for(id=this->x1;id<=this->x2;id++)
        {
            if(state.game_state[id][this->y2+1]!=0)
            {
                return false;
                break;
            }
        }
        return true;
    }

    void moveUp(State& state) {
        for(int id=this->y1;id<=this->y2;id++)
        {
            state.game_state[this->x2][id]=0;
            state.game_state[this->x1-1][id]=this->tile_id;
        }
        this->x1-=1;
        this->x2-=1;
    }
    void moveDown(State& state) {
        for(int id=this->y1;id<=this->y2;id++)
        {
            state.game_state[this->x1][id]=0;
            state.game_state[this->x2+1][id]=this->tile_id;
        }
        this->x1+=1;
        this->x2+=1;
    }
    void moveLeft(State& state) {
        for(int id=this->x1;id<=this->x2;id++)
        {
            state.game_state[id][this->y2]=0;
            state.game_state[id][this->y1-1]=this->tile_id;
        }
        this->y1-=1;
        this->y2-=1;
    }
    void moveRight(State& state) {
        for(int id=this->x1;id<=this->x2;id++)
        {
            state.game_state[id][this->y1]=0;
            state.game_state[id][this->y2+1]=this->tile_id;
        }
        this->y1+=1;
        this->y2+=1;
    }
};

class AStarDemo{
public:
    AStarDemo(){}

    void getInput(State& state, string input_file) {
        string inText;

        ifstream reader(input_file);
        if(!reader) {
            cout<<"\n Error opening the file";
        }
        else {
            getline(reader,inText);
            char w1 = inText.at(0);
            state.w=(int)w1-48;
            char h1 = inText.at(2);
            state.h=(int)h1-48;
            while(!reader.eof()) {
                vector<int> vector1;
                getline(reader,inText);
                if(inText == "") break;
                split(inText,',',vector1);
                state.game_state.push_back(vector1);
            }
        }
    }


    void split(string& inText, char comma, vector<int>& vector1)
    {
        int position = inText.find(comma,0);
        int i=0;
        while(position!=string::npos)
        {
            vector1.push_back(stoi(inText.substr(i, position)));
            i=++position;
            position=inText.find(comma,i);
        }
    }



    void getTileDetails(const State state, vector<Tile>& v_tiles)
    {

        set<int> s;

        vector<int> v;
        for(int m=0 ; m<state.game_state.size() ; m++)
        {
            for(int n=0 ; n<state.game_state[0].size() ; n++)
            {
                if(state.game_state[m][n]>1)
                {
                    s.insert(state.game_state[m][n]);
                }
            }            
        }
        for(set<int>::iterator i = s.begin(); i != s.end(); i++)
        {

            v.push_back(*i);
        }

        // v will consist of distinct values of bricks

        for(int i = 0 ; i < v.size() ; i++) {
            Tile tile;
            tile.tile_id = v[i];
            tile.x1 = 0;
            tile.x2 = 0;
            tile.y1 = 0;
            tile.y2 = 0;

            for(int j = 0; j < state.game_state.size(); j++)
            {
                for(int k = 0; k < state.game_state[0].size(); k++)
                {
                    if(state.game_state[j][k] == tile.tile_id) {
                        if(tile.x1 == 0 && tile.y1 == 0) {
                            tile.x1 = j;
                            tile.y1 = k;
                            tile.x2 = j;
                            tile.y2 = k;
                        }
                        else {
                            tile.x2 = j;
                            tile.y2 = k;
                        }

                    }

                }
            }
            v_tiles.push_back(tile);
        }
    }

    void getAllMovesForAllTiles(State state, vector<Tile>& v_tiles) {
        for(int i=0; i<v_tiles.size(); i++) {
            if(v_tiles[i].checkMoveUp(state)) {
                v_tiles[i].dir[0]= 1;
            }
            if(v_tiles[i].checkMoveDown(state)) {
                v_tiles[i].dir[1]= 1;
            }
            if(v_tiles[i].checkMoveLeft(state)) {
                v_tiles[i].dir[2]= 1;
            }
            if(v_tiles[i].checkMoveRight(state)) {
                v_tiles[i].dir[3]= 1;
            }
        }
    }

    void performMoves(State state, vector<Tile> v_tiles, vector<State>& children_state, vector<int> goal, int heuristic_type) {
        State temp_state = state;
        vector<Tile> temp_tiles=v_tiles;
        for(int i=0; i<v_tiles.size(); i++) {
            if(v_tiles[i].dir[0] == 1) {
                temp_tiles[i].moveUp(temp_state);
                if(heuristic_type == 1) {
                    initializeStateManhatten(temp_state, temp_tiles[i].tile_id, "Up",children_state, goal);
                }
                else if(heuristic_type == 2) {
                    initializeStateEuclidean(temp_state, temp_tiles[i].tile_id, "Up",children_state, goal);
                }
                temp_tiles=v_tiles;
                temp_state = state;
            }
            if(v_tiles[i].dir[1] == 1) {
                temp_tiles[i].moveDown(temp_state);
                if(heuristic_type == 1) {
                    initializeStateManhatten(temp_state, temp_tiles[i].tile_id, "Down",children_state, goal);
                }
                else if(heuristic_type == 2) {
                    initializeStateEuclidean(temp_state, temp_tiles[i].tile_id, "Down",children_state, goal);
                }
                temp_tiles=v_tiles;
                temp_state = state;
            }

            if(v_tiles[i].dir[2] == 1) {
                temp_tiles[i].moveLeft(temp_state);
                if(heuristic_type == 1) {
                    initializeStateManhatten(temp_state, temp_tiles[i].tile_id, "Left",children_state, goal);
                }
                else if(heuristic_type == 2) {
                    initializeStateEuclidean(temp_state, temp_tiles[i].tile_id, "Left",children_state, goal);
                }
                temp_tiles=v_tiles;
                temp_state = state;
            }

            if(v_tiles[i].dir[3] == 1) {
                temp_tiles[i].moveRight(temp_state);
                if(heuristic_type == 1) {
                    initializeStateManhatten(temp_state, temp_tiles[i].tile_id, "Right",children_state, goal);
                }
                else if(heuristic_type == 2) {
                    initializeStateEuclidean(temp_state, temp_tiles[i].tile_id, "Right",children_state, goal);
                }
                temp_tiles=v_tiles;
                temp_state = state;
            }

        }
    }

    void initializeStateManhatten(State& temp_state, int tile_id, string action, vector<State>& children_state, vector<int> goal){
        temp_state.normalize();
        int depth = temp_state.getDepth()+1;
        temp_state.setDepth(depth);
        temp_state.setStateCost(depth+getManhattanDistance(temp_state, goal));
        temp_state.action.push_back("("+std::to_string(tile_id)+","+action+")");
        children_state.push_back(temp_state);
    }
    void initializeStateEuclidean(State& temp_state, int tile_id, string action, vector<State>& children_state, vector<int> goal){
        temp_state.normalize();
        int depth = temp_state.getDepth()+1;
        temp_state.setDepth(depth);
        temp_state.setStateCost(depth+getEuclideanDistance(temp_state, goal));
        temp_state.action.push_back("("+std::to_string(tile_id)+","+action+")");
        children_state.push_back(temp_state);
    }

    int getBestCost(vector<State> open_states) {
        int min_value = open_states[0].state_cost;
        int least_cost_index = 0;
        int temp_cost = 0;
        for(int i=1; i<open_states.size(); i++) {
            temp_cost = open_states[i].state_cost;
            if(temp_cost < min_value) {
                min_value = temp_cost;
                least_cost_index = i;
            }
        }
        return least_cost_index;
    }

    vector<int> getGoalPosition(vector<vector<int>> game_state){
        vector<int> goal={};
        for(int i=0; i<game_state.size(); i++) {
            for(int j=0; j<game_state[0].size(); j++) {
                if(game_state[i][j] == -1) {
                    goal.push_back(i);
                    goal.push_back(j);
                    break;
                }
            }
        }
        return goal;
    }

    void performAstar(State& state, vector<Tile> v_tiles, vector<int> goal, int heuristic_type) {
        vector<State> open_states = {};
        vector<State> closed_states = {};
        vector<State> child_states {};
        state.normalize();
        open_states.push_back(state);
        int best_index = 0, flag_to_check_for_open_list = 0, flag_to_check_for_closed_list = 0;
        State best_state;
        bool goalReached = false;
        do {
            best_index = getBestCost(open_states);
            best_state = open_states[best_index];
            open_states.erase(open_states.begin()+best_index);
            closed_states.push_back(best_state);
            if(best_state.isComplete()) {
                output(best_state, closed_states);
                goalReached=true;
                break;
            }
            else {
                    child_states = getAllChild(best_state, goal, heuristic_type);
                for(int i=0; i<child_states.size(); i++) {
                    flag_to_check_for_open_list = 0; flag_to_check_for_closed_list = 0;
                    for(int j=0; j<open_states.size(); j++) {
                        if(isEqual(child_states[i].getGameState(), open_states[j].getGameState())) {
                            flag_to_check_for_open_list = 1;
                        }
                    }
                    for(int k=0; k<closed_states.size(); k++) {
                        if(isEqual(child_states[i].getGameState(), closed_states[k].getGameState())) {
                            flag_to_check_for_closed_list = 1;
                        }
                    }
                    if(flag_to_check_for_open_list != 1 && flag_to_check_for_closed_list != 1) {
                        open_states.push_back(child_states[i]);
                    }
                }
            }
        }while(!goalReached);
    }

    bool isEqual(vector<vector<int>> game_state1, vector<vector<int>> game_state2) {
        for(int i=0; i<game_state1.size(); i++) {
            for(int j=0; j<game_state1[0].size(); j++) {
                if(game_state1[i][j] != game_state2[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }

    vector<State> getAllChild(State& best_state, vector<int> goal, int heuristic_type) {
        vector<State> children_state = {};
        vector<Tile> v_tiles = {};
        getTileDetails(best_state,v_tiles);
        getAllMovesForAllTiles(best_state,v_tiles);
        performMoves(best_state,v_tiles,children_state, goal, heuristic_type);
        return children_state;
    }

    int getManhattanDistance(State state, vector<int> goal) {
        vector<vector<int>> game_state = state.getGameState();
       int master_brick_x1, master_brick_y1, manhattan_distance =0;
       for(int i=0; i<game_state.size(); i++) {
           for(int j=0; j<game_state[0].size(); j++) {
               if(game_state[i][j] == 2) {
                   master_brick_x1 = i;
                   master_brick_y1 = j;
                   break;
               }
           }
       }
       manhattan_distance = abs((master_brick_x1 - goal[0]) + (master_brick_y1 - goal[1]));
       return manhattan_distance;
    }

    int getEuclideanDistance(State state, vector<int> goal) {
        vector<vector<int>> game_state = state.getGameState();
       int master_brick_x1, master_brick_y1, euclidean_distance =0;
       for(int i=0; i<game_state.size(); i++) {
           for(int j=0; j<game_state[0].size(); j++) {
               if(game_state[i][j] == 2) {
                   master_brick_x1 = i;
                   master_brick_y1 = j;
                   break;
               }
           }
       }
       euclidean_distance = sqrt(((master_brick_x1 - goal[0])*(master_brick_x1 - goal[0])) + ((master_brick_y1 - goal[1])*(master_brick_y1 - goal[1])));
       return euclidean_distance;
    }

    void output(State best_state,const vector<State>& closed_states) {
        vector<string> action = best_state.getAction();
        for(int i=0; i<action.size(); i++) {
            cout << action[i] << endl;
        }
        best_state.display();
        cout << "Total number of nodes visited : " << closed_states.size() << endl;
        cout << "Total number of steps to solve the puzzle : " << action.size() << endl;
    }
};

int main() {
    AStarDemo aStarDemoObject;
    State state_manhatten;
    State state_euclidean;
    vector<string> action={};
    int manhatten = 1;
    int euclidean = 2;
    string input_file = "SBP-level1.txt";
    vector<Tile> v_tiles = {};
    aStarDemoObject.getInput(state_manhatten, input_file);
    vector<int> goal=aStarDemoObject.getGoalPosition(state_manhatten.getGameState());
    state_manhatten.setDepth(0);
    state_manhatten.setStateCost(0+aStarDemoObject.getManhattanDistance(state_manhatten, goal));
    state_manhatten.setAction(action);
    aStarDemoObject.getTileDetails(state_manhatten , v_tiles);
    cout << "Using Manhatten for SBP-level1" << endl;
    clock_t start = clock();
    double duration = 0.0;
    aStarDemoObject.performAstar(state_manhatten,v_tiles, goal,manhatten);
    duration = (clock() - start) / (double) CLOCKS_PER_SEC;
    cout << "Time taken : " << duration << endl;

    v_tiles={};
    aStarDemoObject.getInput(state_euclidean, input_file);
    goal=aStarDemoObject.getGoalPosition(state_euclidean.getGameState());
    state_euclidean.setDepth(0);
    state_euclidean.setStateCost(0+aStarDemoObject.getEuclideanDistance(state_euclidean, goal));
    state_euclidean.setAction(action);
    aStarDemoObject.getTileDetails(state_euclidean , v_tiles);
    cout << "Using Euclidean SBP-level1" << endl;
    start = clock();
    duration = 0.0;
    aStarDemoObject.performAstar(state_euclidean,v_tiles, goal,euclidean);
    duration = (clock() - start) / (double) CLOCKS_PER_SEC;
    cout << "Time taken : " << duration << endl;

    AStarDemo aStarDemoObject1;
    input_file = "SBP-level2.txt";
    v_tiles={};
    state_manhatten = {};
    state_euclidean = {};
    aStarDemoObject1.getInput(state_manhatten, input_file);
    goal=aStarDemoObject1.getGoalPosition(state_manhatten.getGameState());
    state_manhatten.setDepth(0);
    state_manhatten.setStateCost(0+aStarDemoObject1.getManhattanDistance(state_manhatten, goal));
    state_manhatten.setAction(action);
    aStarDemoObject1.getTileDetails(state_manhatten , v_tiles);
    cout << "Using Manhatten for SBP-level2" << endl;
    start = clock();
    duration = 0.0;
    aStarDemoObject1.performAstar(state_manhatten,v_tiles, goal,manhatten);
    duration = (clock() - start) / (double) CLOCKS_PER_SEC;
    cout << "Time taken : " << duration << endl;

    v_tiles={};
    aStarDemoObject1.getInput(state_euclidean, input_file);
    goal=aStarDemoObject1.getGoalPosition(state_euclidean.getGameState());
    state_euclidean.setDepth(0);
    state_euclidean.setStateCost(0+aStarDemoObject1.getEuclideanDistance(state_euclidean, goal));
    state_euclidean.setAction(action);
    aStarDemoObject1.getTileDetails(state_euclidean , v_tiles);
    cout << "Using Euclidean SBP-level2" << endl;
    start = clock();
    duration = 0.0;
    aStarDemoObject1.performAstar(state_euclidean,v_tiles, goal,euclidean);
    duration = (clock() - start) / (double) CLOCKS_PER_SEC;
    cout << "Time taken : " << duration << endl;
    return 0;
}
