#ifndef IMP_TIME_H
#define IMP_TIME_H

// tinh thoi gian dung game va chay game

class ImpTime{
public:
	ImpTime();
	~ImpTime();
	void start();
	void stop();
	void paused();
	void unpaused();

	int get_ticks();
	bool is_started();
	bool is_paused();



private:
	int start_tick_;
	int paused_tick_;

	bool is_paused_;
	bool is_started_;

};



#endif