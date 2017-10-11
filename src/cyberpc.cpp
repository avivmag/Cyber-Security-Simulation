#include "../include/cyberpc.h"
using namespace std;

CyberPC::CyberPC(string cyber_pc_os, string cyber_pc_name) : 
cyber_pc_os_(cyber_pc_os), 
cyber_pc_name_(cyber_pc_name)
{ }

const string CyberPC::getName()
{
  return cyber_pc_name_;
}
   
void CyberPC::AddConnection(string second_pc)		// Add a connection to this PC
{
  cyber_pc_connections_.push_back(second_pc);
}
  
void CyberPC::Infect(CyberWorm & worm) 			// Add a worm to this PC
{
  if(worm.IsWormPrefOs(cyber_pc_os_))
  {
    delete cyber_worm_;
    cyber_worm_ = new CyberWorm(worm);
    cyber_pc_time_to_infect_ = cyber_worm_->GetDormancy();
    cout << "\t\t" << cyber_pc_name_ << " infected by " << cyber_worm_->GetName() << endl;
  }
  else
    cout << "\t\tWorm " << worm.GetName() << " is incompatible with " << cyber_pc_name_ << endl;
}

void CyberPC::Run(const CyberDNS & server) 			// Activate PC and infect others if worm is active	
{
  if(cyber_worm_ != NULL)
  {
    if(cyber_pc_time_to_infect_ <= 0)
    {
      cout << "\t" << cyber_pc_name_ << " infecting..." << endl;
      for (unsigned int i = 0; i!=cyber_pc_connections_.size(); i++)
	server.GetCyberPC(cyber_pc_connections_[i]).Infect(*cyber_worm_);
    }
    else
      cout << "\t" << cyber_pc_name_ << ": Worm " << cyber_worm_->GetName() << " is dormant" << endl;
    
    cyber_pc_time_to_infect_--;
  }
}

void CyberPC::Disinfect()					// called by cyber expert, disinfect PC
{
  if(cyber_worm_ != NULL)
  {
    cout << "\t\tWorm " << cyber_worm_->GetName() << " successfully removed from " << cyber_pc_name_ << endl;
    delete cyber_worm_;
    cyber_worm_ = NULL;
  }
}

// Destructor
CyberPC::~CyberPC()
{
  delete cyber_worm_;
}