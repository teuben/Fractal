#include "libs.hh"
#include "classes.hh"
#include "headers.hh"
namespace FractalSpace
{
  void total_mass(Fractal_Memory& mem)
  {
    if(!mem.periodic)
      {
	mem.p_fractal->set_density_0(0.0);
	return;
      }
    double mm=0.0;
    // for(auto ppoints:mem.all_groups[0][0]->list_points)
    //   for(auto ppart:ppoints->list_particles)
    // 	mm+=ppart->get_mass();
    vector<double>tm={mm};
    mem.p_mess->Find_Sum_DOUBLE(tm,1);
    mem.p_fractal->set_density_0(tm[0]);
    if(mem.p_mess->FractalRank==0)
      cerr << " Total Mass " << mm << " " << tm[0] << " " << "\n";
  }
}
