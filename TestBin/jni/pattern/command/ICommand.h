/*
 * ICommand.h
 *
 *  Created on: 2018-5-2
 *      Author: YC2
 */

#ifndef ICOMMAND_H_
#define ICOMMAND_H_

#include "Log.h"
#include "list"

using namespace std;
//命令接口
class Command{
public:
	virtual ~Command(){}
	virtual void executed() = 0;
protected:
	Command(){}
};

//命令的执行者
class Receiver{
public:
	Receiver(){}
	~Receiver(){}
	void actionRice(){
		LOGI("cook rice");
	}

	void actionNoodle(){
		LOGI("cook noodle");
	}
};

//命令中转者A
class ConcreteCommandA:public Command{
public:
	ConcreteCommandA(Receiver* pReceiver){
		m_pReceiver = pReceiver;
	}
	~ConcreteCommandA(){}
	virtual void executed(){
		m_pReceiver->actionRice();
	}

private:
	Receiver* m_pReceiver;
};

//命令中转者B
class ConcreteCommandB:public Command{
public:
	ConcreteCommandB(Receiver* pReceiver){
		m_pReceiver = pReceiver;
	}
	~ConcreteCommandB(){}
	virtual void executed(){
		m_pReceiver->actionNoodle();
	}

private:
	Receiver* m_pReceiver;
};

//所有命令的管理者
class Invoke{
public:
	Invoke(){}
	~Invoke(){}
	void addCommand(Command* pCmd){
		m_commandList.push_back(pCmd);
	}

	void delCommand(Command* pCmd){
		list<Command*>::iterator it_B = m_commandList.begin();
		list<Command*>::iterator it_E = m_commandList.end();
		while(it_B != it_E){
			if ((*it_B) == pCmd){
				delete *it_B;
				m_commandList.erase(it_B);
				break;
			}
			it_B++;
		}
	}

	void sendCommand(){
		list<Command*>::iterator it_B = m_commandList.begin();
		list<Command*>::iterator it_E = m_commandList.end();
		while(it_B != it_E){
			(*it_B)->executed();
			it_B++;
		}
	}
private:
	typedef std::list<Command *> COMMANDLIST;
	COMMANDLIST m_commandList;
};

#endif /* ICOMMAND_H_ */
