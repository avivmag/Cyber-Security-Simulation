#include "../include/cyberdns.h"
using namespace std;

CyberDNS::CyberDNS()
{ }

void CyberDNS::AddPC(CyberPC & cyber_pc_)
{
  cyber_DNS_.insert(pair<const string,CyberPC &>(cyber_pc_.getName(),cyber_pc_));
}

CyberPC &  CyberDNS::GetCyberPC(const string & cyber_pc_name) const
{
  return cyber_DNS_.at(cyber_pc_name);
}

vector<string> CyberDNS::GetCyberPCList()
{
   vector<string> ans;
   for(map<string, CyberPC &>::reverse_iterator it = cyber_DNS_.rbegin(); it != cyber_DNS_.rend(); it++) {
     ans.push_back(it->first);
   }
   return ans;
}

bool CyberDNS::IsComputerExist(string name)
{
  return cyber_DNS_.count(name);
}

CyberDNS::~CyberDNS()
{
  for (map<const string, CyberPC &>::iterator it = cyber_DNS_.begin(); it != cyber_DNS_.end(); ++it){
   delete &(it->second);
  }
}
