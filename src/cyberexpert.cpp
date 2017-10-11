#include "../include/cyberexpert.h"
using namespace std;

CyberExpert::CyberExpert(string cyber_expert_name, int cyber_expert_work_time, int cyber_expert_rest_time, int cyber_expert_efficiency) :
cyber_expert_name_(cyber_expert_name),
cyber_expert_work_time_(cyber_expert_work_time),
cyber_expert_rest_time_(cyber_expert_rest_time),
cyber_expert_efficiency_(cyber_expert_efficiency)
{
  //if it's -1, it means it is not time for the expert for the specific activity
  daysRemainToWork = cyber_expert_work_time_;
  daysOffRemain = -1;
  
  cout << "\tClock-In: " << cyber_expert_name_ << " began working" << endl;
}

void CyberExpert::Clean(CyberPC & cyber_pc)
{
  cout << "\t" << cyber_expert_name_ << " examining " << cyber_pc.getName() << endl;
  cyber_pc.Disinfect();
}

// update the expert that day has passed
void CyberExpert::DayPassed()
{
  // if expert is currently resting
  if(daysRemainToWork == -1)
  {
    daysOffRemain--;
	// if that was the last day off
    if(daysOffRemain == 0)
    {
      daysOffRemain = -1;
      daysRemainToWork = cyber_expert_work_time_;
	cout << "\t" << cyber_expert_name_ << " is back to work" << endl;
    }
  }
  // if this worker is working (the checking also makes sure the program works fine)
  else if(daysOffRemain == -1)
  {
    daysRemainToWork--;
    if(daysRemainToWork == 0)
    {
      if(cyber_expert_rest_time_ == 0)
      {
	daysRemainToWork = cyber_expert_work_time_;
      }
      else
      {
	daysRemainToWork--; 
	daysOffRemain = cyber_expert_rest_time_;
	cout << "\t" << cyber_expert_name_ << " is taking a break" << endl;
      }
    }
  }
}

unsigned int CyberExpert::GetEfficiency()
{
  return daysRemainToWork > 0 ? cyber_expert_efficiency_ : 0;
}