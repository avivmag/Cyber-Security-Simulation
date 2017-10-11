#include "../include/cyberworm.h"
using namespace std;

CyberWorm::CyberWorm(std::string cyber_worm_os, std::string cyber_worm_name, int cyber_worm_dormancy_time) : 
cyber_worm_os_(cyber_worm_os),
cyber_worm_name_(cyber_worm_name), 
cyber_worm_dormancy_time_(cyber_worm_dormancy_time)
{ }

CyberWorm::CyberWorm(const CyberWorm& other) :
cyber_worm_os_(other.cyber_worm_os_),
cyber_worm_name_(other.cyber_worm_name_),
cyber_worm_dormancy_time_(other.cyber_worm_dormancy_time_)
{ }

bool CyberWorm::IsWormPrefOs(std::string prefOs)
{
  return cyber_worm_os_ == prefOs;
}

string CyberWorm::GetName()
{
  return cyber_worm_name_;
}

int CyberWorm::GetDormancy()
{
  return cyber_worm_dormancy_time_;
}