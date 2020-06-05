#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <set>
#include <chrono>
#include <thread>

using namespace std;
struct Time{
	int day; // bw 1 to 5, 0 -> mon
	int hour; // 1 -> 24
	int min;// 1 -> 60

	int convertMin(){
		int time = min + (hour*60);
		return time;
	}

	string toString(){
		stringstream ss;
		ss << day <<", " <<hour << ", " << min;
		string s = ss.str();
		return s;
	}

};

struct Interval{
	Time startTime;
	Time endTime;

	static bool isIntersecting(Interval a, Interval b){
		int a_stime = a.startTime.convertMin();
		int b_stime = b.startTime.convertMin();
		int a_etime = a.endTime.convertMin();
		int b_etime = b.endTime.convertMin();
		if(a.startTime.day==b.startTime.day){
			if(b_stime>=a_stime && b_stime<=a_etime){
				return true;
			}
			else if (b_etime>=a_stime && b_etime<=a_etime){
				return true;
			}
			return false;
		}
		else{
			return false;
		}
	}


	void print(){
		cout<<(startTime).toString()<<" :: "<<(endTime).toString();
	}

	string to_string(){
		return startTime.toString() + " to " + endTime.toString();
	}
};

struct Section{
	string major, number;
	string subsection;
	string session;
	string type;
  	string rawTime;
  	string rawDays;
    int currentRegistered;
    int maxRegistered;
    string instructor;
    string location;


    vector<Interval> intervals;


    bool operator<(const Section& other) const{
    	return subsection < other.subsection;
    }

    //convert rawTime and rawDays to vector of intervals
    void process(){


    	//handle TBA

    	if(rawTime == "TBA" || rawDays == "TBA"){
    		//make it tba
    		return;
    	}

    	//read the raw Time and make it from start to end

    	bool isPm = (rawTime.substr(rawTime.length()-2, 2) == "pm"); // true if pm

    	string rest = rawTime.substr(0, rawTime.length()-2);
    	//remove the hyphen
    	string rawStartTime = rest.substr(0, rest.find("-"));
    	string rawEndTime   = rest.substr(rawStartTime.length()+1);

    	//remove the colons
    	Time startTime, endTime;

    	//still need to figure out am or pm
    	startTime.hour = stoi(rawStartTime.substr(0, rawStartTime.find(":")));
    	startTime.min = stoi(rawStartTime.substr(rawStartTime.find(":")+1));
    	
    	endTime.hour = stoi(rawEndTime.substr(0, rawEndTime.find(":")));
    	endTime.min = stoi(rawEndTime.substr(rawEndTime.find(":")+1));

    	if(isPm){
    		if(endTime.hour < 12) endTime.hour += 12;
    	}
    	else{
    		if(endTime.hour == 12) endTime.hour = 0;
    	}

    	if(isPm){
    		if(startTime.hour < 12) startTime.hour += 12;
    	}else{
    		if(startTime.hour == 12) startTime.hour = 0;
    	}

    	if(startTime.hour > endTime.hour) startTime.hour -= 12; // THIS IS NOT REDUNDANT. DO NOT REMOVE THIS



    	//first step is to read rawDays and figure out which days are there


    	map<string, int> conv;

    	conv["M"] = 0;
    	conv["T"] = 1;
    	conv["W"] = 2;
    	conv["F"] = 4;
 
 		conv["Mo"] = 0;
    	conv["Tu"] = 1;
    	conv["We"] = 2;
    	conv["Th"] = 3;
    	conv["Fr"] = 4;
 
    	

    	rawDays += " ";
    	for(int i = 0; i < rawDays.length(); i++){
    		//if letter is capital
    		if(rawDays[i] >= 'A' && rawDays[i] <= 'Z'){
    			//cout<<"INDEX: "<<i<<" "<<rawDays[i]<<" jsdjkc"<<endl;
    			for(int j = i+1; j < rawDays.length(); j++){
    				if(!(rawDays[j] >= 'a' && rawDays[j] <= 'z')){
    					//break string from i to j-1
    					string cur = rawDays.substr(i, j-i);

    					cur = cur.substr(0, 2); //shrink it to 2 chars, if it is longer

    					int dayVal = conv[cur];
    					Time startTimeFinal = {dayVal, startTime.hour, startTime.min};
    					Time endTimeFinal = {dayVal, endTime.hour, endTime.min};
    					Interval intFinal = {startTimeFinal, endTimeFinal};
    					intervals.push_back(intFinal);
    					break;
    				}
    			}
    		}
    	}

    	//then add everything in intervals

    	// cout<<"SIZE: "<<intervals.size()<<endl;
    	// for(int i = 0; i < intervals.size(); i++){
    	// 	cout<<"INTERVAL "<<i+1<<" : "; 
    	// 	intervals[i].print();
    	// 	cout<<endl;
    	// }
    }

    void print(){
    	// cout << subsection <<endl;
    	// cout << session <<endl;
    	// cout << type <<endl;
    	// //cout << startTime <<endl;
    	// //print time
    	// //cout << endTime <<endl;
    	// //cout << days <<endl;
    	// cout << currentRegistered <<endl;
    	// cout << maxRegistered <<endl;
    	// cout << instructor <<endl;
    	// cout << location <<endl;



    	cout<<"SECTION: "<<major<<" "<<number<<" "<<subsection<<" "<<endl;
    }

    string to_string(){
    	string s = "SECTION: " + major + " " + number + " " + type + " " + subsection + " INTERVALS: \n";
    	for(Interval inter: intervals){
    		s += inter.to_string() + "\n";
    	}
    	s += "SECTION DONE\n";
    	return s;
    }
};

struct Topic {
	string major, number;
	vector<Section> sections;
	//mera naam chin chin chu


	void print(){
		for (int i=0; i<sections.size(); i++){
			sections[i].print();
		}
		cout << endl;
	}
};


Section readSection(string line){
	stringstream ss(line);
	Section section;
	string cur;

	getline(ss, cur, ',');
	section.subsection = cur;

	getline(ss, cur, ',');
	section.session = cur;

	getline(ss, cur, ',');
	section.type = cur;	

	getline(ss, cur, ',');
	section.rawTime = cur;	

	getline(ss, cur, ',');
	section.rawDays = cur;	

	getline(ss, cur, ',');
	section.currentRegistered = stoi(cur);

	getline(ss, cur, ',');
	section.maxRegistered = stoi(cur);

	getline(ss, cur, ',');
	section.instructor = cur;	

	getline(ss, cur, '\n'); //last word has to be dellimed by \n
	section.location = cur;	

	return section;
}

Topic readTopic(string fileName, string name, string code){
	ifstream inputText(fileName);

	Topic topic;
	topic.major = name;
	topic.number = code;

	if (inputText.fail()) {
		cout << "Unable to open file" << endl;
    	return topic; // if it fails what to return
    }

    string temp;
    
	while(!inputText.fail()){
		getline(inputText, temp);
		if(inputText.fail()){
			break;
		}
		Section section = readSection(temp);
		section.major = name;
		section.number = code;
		section.process();
		topic.sections.push_back(section);
	}
	return topic;
}


vector<Topic> topics;
set<Section> stack;

struct Schedule{
	vector<Section> sections;
	int daysOff = 0;
	double stddev = 0;
	void print(){
		cout<<"PRINTING SCHEDULE "<<endl;
		for(int i = 0; i < sections.size(); i++){
			cout<<sections[i].to_string()<<endl;
		}
		cout<<"__________________"<<endl;
	}

	void process(){
		vector<int> times(5);
		int sum = 0;
		for(int d = 0; d < 5; d++){
			int count = 0;
			int time = 0;
			Time startTime = {d, 24, 0};
			Time endTime = {d, 0, 0};
			for(int i = 0; i < sections.size(); i++){
				Section& cur = sections[i];
				if(cur.type == "Quiz") continue;
				
				for(Interval intr : cur.intervals){
					if(intr.startTime.day != d) continue;
					count += 1;
					time += (intr.endTime.convertMin()) - (intr.startTime.convertMin());
					if(intr.endTime.convertMin() > endTime.convertMin()){
						endTime = intr.endTime;
					}

					if(intr.startTime.convertMin() < startTime.convertMin()){
						startTime = intr.startTime;
					}
				}	
			}

			times[d] = time;
			sum += time;
		}

		//calc standard dev and number of days off
		for(int i = 0; i < times.size(); i++){
			daysOff += times[i] == 0;
		}
		int mean = sum/(5 - daysOff);
		for(int i = 0; i < times.size(); i++){
			if(times[i] > 0) stddev += (times[i] - mean)*(times[i]- mean);
		}
		stddev = (sum*1.00/(5- daysOff));
	}


	string serializeSchedule(){
		string s; 
		for(int i = 0; i < sections.size(); i++){
			Section& cur = sections[i];
			s += cur.major + ", " + cur.number + ", " + cur.type + ", " + cur.rawTime + ", " + cur.rawDays + ", " + cur.instructor + "\n";
		}
		return s;
	}
	string serialize(){
		string s;
		vector<string> days = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};
		//number of classes on each day
		for(int d = 0; d < 5; d++){
			int count = 0;
			int time = 0;
			Time startTime = {d, 24, 0};
			Time endTime = {d, 0, 0};
			for(int i = 0; i < sections.size(); i++){
				Section& cur = sections[i];
				if(cur.type == "Quiz") continue;
				
				for(Interval intr : cur.intervals){
					if(intr.startTime.day != d) continue;
					count += 1;
					time += (intr.endTime.convertMin()) - (intr.startTime.convertMin());
					if(intr.endTime.convertMin() > endTime.convertMin()){
						endTime = intr.endTime;
					}

					if(intr.startTime.convertMin() < startTime.convertMin()){
						startTime = intr.startTime;
					}
				}	
			}
			s += days[d] + ": " + to_string(count) + " classes of " + to_string(time) + " minutes\n";
			s += "Day starts at " + to_string(startTime.hour) + ":" + to_string(startTime.min) + " and ends at "+ to_string(endTime.hour) + ":" + to_string(endTime.min) + "\n";
		}

		return s;
	}

	static bool sortByDaysOff(Schedule a, Schedule b){
		return a.daysOff > b.daysOff;
	}

	static bool optimumSort(Schedule a, Schedule b){
		if(a.daysOff == b.daysOff) return a.stddev < b.stddev;
		return a.daysOff > b.daysOff;
	}

};

vector<Schedule> valid;
int minHour; 

bool validate(Section check){
	if(check.currentRegistered >= check.maxRegistered) return false;
	for(Interval checkC: check.intervals){
		if(checkC.startTime.hour < minHour) return false;
		for(Section other: stack){
			for(Interval oint: other.intervals){
				if(Interval::isIntersecting(oint, checkC)) return false;	
			}	
		}	
	}
	return true;
}

//main algorithm to generate all the schedules in the valid
void rec(int indx, int state, int lectureID){
	//queue up lectures discussions lab quiz

	if(indx == -1){
		//reached end
		Schedule curSched; curSched.sections.reserve(stack.size());
		for(Section curSection: stack){
			curSched.sections.push_back(curSection);
		}
		valid.push_back(curSched);
		valid.back().process();
		return;
	}

	//first select a lecture
	//then select a discussion
	//then select a lab
	//then select a quiz
	Topic& topic = topics[indx];

	if(state == 0){ //lecture

		bool found = false;
		for(int i = 0; i < topic.sections.size(); i++){
			if(topic.sections[i].type == "Lecture"){
				//chose this if it doesnt intersect
				found = true;
				if(validate(topic.sections[i])){
					//add it, recurse, then remove
					stack.insert(topic.sections[i]);
					rec(indx, state+1, i);
					stack.erase(topic.sections[i]);
				}

			}
		}
		if(!found){
			rec(indx-1, 0, -1); // go to next class
		}

	}else if(state == 1){ //discussions
		bool found = false;
		for(int i = lectureID+1; i < topic.sections.size(); i++){
			if(topic.sections[i].type == "Discussion"){
				//chose this if it doesnt intersect
				found = true;
				if(validate(topic.sections[i])){
					//add it, recurse, then remove
					stack.insert(topic.sections[i]);
					rec(indx, state+1, i);
					stack.erase(topic.sections[i]);
				}
			}else if(topic.sections[i].type == "Lecture"){
				//if a discussion came between this, then break
				if(found) return;
			}
		}
		if(!found){
			rec(indx, 2, lectureID); // go to labs
		}
	}else if(state == 2){ //lab
		bool found = false;
		for(int i = 0; i < topic.sections.size(); i++){
			if(topic.sections[i].type == "Lab"){
				//chose this if it doesnt intersect
				found = true;
				if(validate(topic.sections[i])){
					//add it, recurse, then remove
					stack.insert(topic.sections[i]);
					rec(indx, state+1, lectureID);
					stack.erase(topic.sections[i]);
				}

			}
		}
		if(!found){
			rec(indx, 3, lectureID); // go to quiz
		}
	}else if(state == 3){ //quiz
		bool found = false;
		for(int i = 0; i < topic.sections.size(); i++){
			if(topic.sections[i].type == "Quiz"){
				//chose this if it doesnt intersect
				found = true;
				if(validate(topic.sections[i])){
					//add it, recurse, then remove
					stack.insert(topic.sections[i]);
					rec(indx-1, 0, -1);
					stack.erase(topic.sections[i]);
				}

			}
		}
		if(!found){
			rec(indx-1, 0, -1); // go to next class
		}
	}
}
 
int main(int argc, char* argv[]) {
	// Topic topic = readTopic("csci103.csv");
	// topic.print();

	//bllahahah blahha
	//get the vector of topics without any filters for now

	cout<<"WELCOME TO THE USC SCHEDULER!"<<endl;
	cout<<"ENTER THE NUMBER OF CLASSES YOU WISH TO TAKE"<<endl;
	int count; cin>>count;

	for(int i = 0; i < count; i++){

		string run_prog = "python3 WebScraperUSC.py";
		cout << "Please enter your course name and code seperately" << endl;
		string name, code;
		cin >> name >> code;
		run_prog = run_prog + " " + name + " " + code;
		ifstream ifile(name + code + ".csv");

		if(ifile.fail()){
			system("pwd");
			system(run_prog.c_str());
			cout<<"FETCHING RESULTS FROM USC WebReg"<<endl;
			std::this_thread::sleep_for(std::chrono::milliseconds((int)3e3));
			cout<<"Done Fetching"<<endl;	
		}
		else{
			cout<<"FOUND FILE"<<endl;
			ifile.close();
		}
		

		topics.push_back(readTopic(name + code + ".csv", name, code));

	}

	cout<<"What is the earliest class you would like. Enter the hour: ";
	cin>>minHour;


	rec(topics.size()-1, 0, -1);
	
	cout<<"GENERATED "<<valid.size()<<" SCHEDULES "<<endl;
	sort(valid.begin(), valid.end(), Schedule::optimumSort);
	for(int i = 0; i < 5 && i < valid.size(); i++){
		string a = valid[i].serializeSchedule();
		string b = valid[i].serialize();

		ofstream out("Sched" + to_string(i+1) + ".txt");
		out<<a<<endl;
		out.close();
		out = ofstream("Sched" + to_string(i+1) + "a.txt");
		out<<b<<endl;
	}

	string run_prog1 = "python3 gui.py";
	system("pwd");
	system(run_prog1.c_str());

    return 0;
}
    