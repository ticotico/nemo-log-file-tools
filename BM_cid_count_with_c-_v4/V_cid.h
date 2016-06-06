#ifndef V_CID_H
#define V_CID_H
#include "my_vector.h"
#include <string>
class cellID {
	protected:
		char* system;
		int channel;
		int count;
	public:
		cellID()	{ count = 1;}
		bool issamecell(cellID& cid2) const	{
			return (system == cid2.system && channel == cid2.channel /*&& id == cid2.id*/);
		}
		bool operator == (const cellID& cid2) {
			return (system == cid2.system && channel == cid2.channel /*&& id == cid2.id*/);
		}
		void set (char* s, int ch/*, std::string cid*/)	{
			system = s;	channel = ch; /*id = cid;*/ count = 1;
		}
		void inc_count()	{
			count++;
		}
		void print();
		friend void output(cellID&, std::ofstream&);
};

class cellLTE : public cellID {
private:
	int id;
public:
	bool issamecell(cellLTE& cid2) const	{
		return (issamecell(cid2) && id == cid2.id);
	}
	bool operator == (const cellLTE& cid2) {
		return (cellID::operator == (cid2)  && id == cid2.id);
	}
	void set(char* s, int ch, int cid) {
		cellID::set (s, ch); id = cid;
	}
	
	void print();
	friend void output(cellLTE&, std::ofstream&);
};

class cellUMTS : public cellID {
private:
	std::string id;
public:
	bool issamecell(cellUMTS& cid2) const	{
		return (issamecell(cid2) && id == cid2.id);
	}
	bool operator == (const cellUMTS& cid2) {
		return (cellID::operator == (cid2)  && id == cid2.id);
	}
	void set(char* s, int ch, std::string cid) {
		cellID::set (s, ch); id = cid;
	}
	
	void print();
	friend void output(cellUMTS&, std::ofstream&);
};
typedef MY_VECTOR<cellUMTS> V_UMTS_id;
typedef MY_VECTOR<cellLTE> V_LTE_id;
#endif
