	
#include "daePackUnpack.h"
// std::vector< daex::Atom*> globalAtoms;

using namespace daex; 

 extern std::vector< daex::Atom*>  daex::globalAtoms; 
 	
	void pack( daex::Decomposition  & _eo)
		{	
		  if ( _eo.invalid() ) 
    			pack( (unsigned int)0 );
		  else
		    {
		      	pack( (unsigned int)1 );
      			
			  pack(_eo.fitness());
		    }
		 
   		unsigned len = _eo.size();

		pack(len);
	
  		std::list<Goal>::iterator it;

		for ( it=_eo.begin() ; it != _eo.end(); it++ )
		    
    			pack (*it); ///pack each goal
				
		pack(_eo. plan());
		
		pack(_eo.subplans());

		pack(_eo. b_max());

		pack(_eo.get_number_evaluated_goals());
		
		pack(_eo.get_number_useful_goals());

		pack(_eo.get_number_evaluated_nodes());
 
	 }

	void unpack (daex::Decomposition  & _eo)
	{

		unsigned valid, len, _b_max, _k, _u, _B; 

		 eoMinimizingDualFitness fit;

		unpack(valid);
		
  		if (! valid)

    
      			_eo.invalidate();
    
  		else
    		{
    			      			
			  unpack (fit);
      		
			_eo.fitness (fit);
     			
		}

  		unpack (len);

 		_eo.clear();
  
   		//std::list<Goal>::iterator it;

		daex::Goal _goal(0) ; ///voir le constructeur par défaut ?

		for (unsigned i =0; i < len; i++){

			unpack(_goal);
		
			_eo.push_back(_goal);
		}

		Plan _plan_global;

    
    		std::vector< Plan > _plans_sub;
		
		unpack(_plan_global);
		
		unpack(_plans_sub);

		unpack(_b_max);
		
		_eo.b_max(_b_max);

		unpack(_k);

		_eo.reset_number_evaluated_goals();
		
		_eo.incr_number_evaluated_goals(_k);
		
		unpack(_u);

		_eo.reset_number_useful_goals();

		_eo.incr_number_useful_goals(_u);

		unpack(_B);

		_eo.reset_number_evaluated_nodes();

		_eo.incr_number_evaluated_nodes(_B);	
	}



	void pack(    Plan   &  _plan_global )
	{

		pack( _plan_global.makespan());
		
		pack(_plan_global.search_steps());

		pack(_plan_global.isValid());///il falait un accesseur sur _is_valid

// 		unsigned len = _plan_global.plan_rep().size();
// 
// 		for ( unsigned i =0; i < len ; i++)
// 			pack(_plan_global.plan_rep()[i]);
			
	}

	void unpack(  Plan &  _plan_global )
	{

		TimeVal _makespan;

		unsigned _search_steps;

		bool _is_valid;

		unpack(_makespan); ///mutateur sur makespan
		
		_plan_global.makespan(_makespan);

		unpack(_search_steps);

		_plan_global.search_steps(_search_steps);

		unpack(_is_valid);
		
		_plan_global.isValid(_is_valid);

		unsigned len;

		unpack(len);

		_plan_global.plan_rep().resize(len);

		char ch;

		for ( unsigned i =0; i < len ; i++){
			unpack(ch);
			_plan_global.plan_rep()[i]= ch;
			}
	}


	void pack(    std::vector< Plan >  & _plans_sub)
	{
		unsigned len = _plans_sub.size();
		
		pack(len);

		for(size_t i =0; i<len; i++)

			pack(_plans_sub[i]);

	}
	
	void unpack(std::vector< Plan >&  _plans_sub)
	{

		unsigned len;

		unpack(len);

		_plans_sub.resize(len);

		for( size_t i =0; i < len ; i++)

			unpack(_plans_sub[i]);
	
	}

	void pack(    Goal  & _goal){

		 
		unsigned len = _goal.size();

		pack(len);

		std::list<Atom*>::iterator it;   

		for ( it=_goal.begin() ; it != _goal.end(); it++ )
		    
    			//pack (*it); ///pack the atom not the pointer
    			pack( (*it) ->  fluentIndex());


		// pack(_goal.earliest_start_time());

	}


	void unpack(Goal &_goal){ // il falait voir comment faire pour la structure goal etant donné qu'elle est une structure list de pointeurs d'atomes !!!! ( à revoir)

		 
		//std::list<Atom*>::iterator it;   

		//Atom * patom = new Atom (0,0);

		Atom  _atom(0,0);  ///constructeur par défaut ?
				
		unsigned len;

		unpack(len);

// 		for (std::list<Atom*> patom = _goal.begin(); patom != _goal.end();  patom++)
//   		
// 			delete *patom;

		_goal.clear();
		
		unsigned index_atom;

		for ( size_t i = 0; i < len ; i++) {

			unpack(index_atom);
			
			_goal.push_back(daex::globalAtoms[index_atom]); 

// 			 unpack (*patom);
		
// 			_goal.push_back(new 
// 			Atom(patom -> earliest_start_time(),patom -> fluentIndex())); 


			//_goal.push_back(new 
			//Atom(_atom.earliest_start_time(),_atom.fluentIndex()))
			
		}

		//delete patom;

/*
		TimeVal d;  /// c quoi ce type ?

		unpack(d);

		_goal.earliest_start_time(d);*/

	}
	

	void pack(    Atom  & _atom){

		pack(_atom.earliest_start_time());

		pack(_atom.fluentIndex());  

	}


	void unpack(Atom & _atom){

		
		TimeVal  _earliest_start_time;

		unsigned _fluent;

		unpack(_earliest_start_time);

		_atom.earliest_start_time (_earliest_start_time);

		unpack(_fluent);

		_atom.fluentIndex(_fluent);


	}

/*

	void pack (  const eoMinimizingDualFitness  &  fit)  {   //eoMinimizingDualFitness

		pack(fit.value());

		pack(fit.is_feasible());

	};




	void unpack (eoMinimizingDualFitness &  fit) {

		double value;

		bool is_feasible;

		unpack(value);

		unpack(is_feasible);
	
		fit.setValue(value);

		fit.setFeasible(is_feasible);

	}	


 
	
	void pack (   std::pair<double,bool> & v) {

		 
 		pack(v.first);
 
 		pack(v.second);


	}


 
	void unpack (std::pair<double,bool>& v) {

			
		unpack(v.first);

		unpack(v.second);


	}*/

// 	void pack(  eoMinimizingDualFitness &   fit)  {
// 
// 		pack(fit.value());
// 
// 		pack(fit.is_feasible());
// 
// 	}
// 
// 	void unpack(eoMinimizingDualFitness  & fito) { 
// 
// 		
// 
// 		double value ;
// 
// 		bool is_feasible;
// 
// 		unpack(value);
// 
// 		unpack(is_feasible);
// 
// 		//eoMinimizingDualFitness  * pfitness  = new eoMinimizingDualFitness (value,is_feasible); 
// 
// 		// eoMinimizingDualFitness fitness (value,is_feasible); 
// 
// 		//std::pair < double, bool> fitness;
// 
// 
//                 //fitness = std::make_pair (value,is_feasible);
// 
// 		//eoDualFitness< double, std::less<double> > fitness (value,is_feasible);
// 
// 		
// 		fito.setValue(value);
// 
// 		fito.setFeasible(is_feasible);
// 
// 		//fit = * pfitness;
// 
// 	//delete pfitness;
// 
// 	}




