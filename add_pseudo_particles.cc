#include "libs.hh"
#include "classes.hh"
#include "headers.hh"
namespace FractalSpace
{
  void add_pseudo_particles(Fractal_Memory& mem,Fractal& frac)
  {
    if(!mem.periodic)
      return;
    if(Mess::IAMROOT)
      cerr << " Enter Add " << frac.get_number_particles() << " " << Particle::number_particles << endl;
    int length=mem.grid_length;
    double Rdelta=1.0/static_cast<double>(length);
    double Rlow=-2.0*Rdelta;
    double Rhigh=1.0+Rdelta;
    vector <double>pos(3);
    vector<double>boxinner{0.0,1.0,0.0,1.0,0.0,1.0};
    vector<double>boxouter{Rlow,Rhigh,Rlow,Rhigh,Rlow,Rhigh};
    clean_deque(frac.pseudo_particle_list);
    vector <double> posp(3);
    for(int particle=0; particle < frac.get_number_particles(); ++particle)
      {
	Particle* P=frac.particle_list[particle];
	P->get_pos(pos);
	for(int nz=-1;nz<=1;nz++)
	  {
	    posp[2]=pos[2]+nz;
	    for(int ny=-1;ny<=1;ny++)
	      {
		posp[1]=pos[1]+ny;
		for(int nx=-1;nx<=1;nx++)
		  {
		    posp[0]=pos[0]+nx;
		    if(nz==0 && ny==0 && nx==0)
		      continue;
		    if(vector_in_box(posp,boxinner))
		       continue;
		    if(!vector_in_box(posp,boxouter))
		       continue;
		    double m=P->get_mass();
		    Particle* Pb=new Particle;
		    Pb->set_posm(posp,m);
		    Pb->set_real_particle(false);
		    frac.particle_list.push_back(Pb);
		    frac.pseudo_particle_list.push_back(Pb);
		  }
	      }
	  }
      }
    frac.set_number_particles(frac.particle_list.size());
    if(Mess::IAMROOT)
      cerr << " Exit Add " << frac.get_number_particles() << " " << Particle::number_particles << endl;
  }
}
