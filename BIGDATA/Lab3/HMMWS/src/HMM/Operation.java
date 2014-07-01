package HMM;

import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.Reader;
import java.util.List;

import javax.ws.rs.Consumes;
import javax.ws.rs.GET;
import javax.ws.rs.PUT;
import javax.ws.rs.Path;
import javax.ws.rs.PathParam;
import javax.ws.rs.Produces;
import javax.ws.rs.QueryParam;
import javax.ws.rs.core.Context;
import javax.ws.rs.core.UriInfo;

import be.ac.ulg.montefiore.run.jahmm.Hmm;
import be.ac.ulg.montefiore.run.jahmm.ObservationVector;
import be.ac.ulg.montefiore.run.jahmm.OpdfMultiGaussianFactory;
import be.ac.ulg.montefiore.run.jahmm.io.FileFormatException;
import be.ac.ulg.montefiore.run.jahmm.io.ObservationSequencesReader;
import be.ac.ulg.montefiore.run.jahmm.io.ObservationVectorReader;
import be.ac.ulg.montefiore.run.jahmm.learn.BaumWelchLearner;
import be.ac.ulg.montefiore.run.jahmm.learn.KMeansLearner;

@Path("generic")
public class Operation {
    @SuppressWarnings("unused")
    @Context
    private UriInfo context;
    
    Hmm<ObservationVector> learntHmmPunch=null;
	Hmm<ObservationVector> learntHmmScrolldown=null;
	Hmm<ObservationVector> learntHmmSend=null;

    /**
     * Default constructor. 
     */
    public Operation() {
        // TODO Auto-generated constructor stub
    }

    /**
     * Retrieves representation of an instance of Operation
     * @return an instance of String
     */
    @GET
    @Produces("application/x-javascript")
    @Path("HMMTrainingTest/{filename:.+}/{k}")
    public String HMMTraining(@QueryParam("callback") String callback, @PathParam("filename") String filename,
    		@PathParam("k") String k) {
        String line="";
        
        
    	
    	int number = Integer.parseInt(k);
     // Create HMM for punch gesture
  	  
        OpdfMultiGaussianFactory initFactoryPunch = new OpdfMultiGaussianFactory(
                3);

        Reader learnReaderPunch;
		try {
			learnReaderPunch = new FileReader(
					filename);
		
        List<List<ObservationVector>> learnSequencesPunch = ObservationSequencesReader
                .readSequences(new ObservationVectorReader(), learnReaderPunch);
        learnReaderPunch.close();
		

        KMeansLearner<ObservationVector> kMeansLearnerPunch = new KMeansLearner<ObservationVector>(
                number, initFactoryPunch, learnSequencesPunch);
        // Create an estimation of the HMM (initHmm) using one iteration of the
        // k-Means algorithm
        Hmm<ObservationVector> initHmmPunch = kMeansLearnerPunch.iterate();

        line="training success";
        
        // Use BaumWelchLearner to create the HMM (learntHmm) from initHmm
        BaumWelchLearner baumWelchLearnerPunch = new BaumWelchLearner();
         learntHmmPunch = baumWelchLearnerPunch.learn(
                initHmmPunch, learnSequencesPunch);
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			line = e.toString();
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			line = e.toString();
			e.printStackTrace();
		} catch (FileFormatException e) {
			// TODO Auto-generated catch block
			line = e.toString();
			e.printStackTrace();
		}

		
		
		 try {  
		        Reader testReader = new FileReader(
		        		filename);
		        List<List<ObservationVector>> testSequences;
				
					testSequences = ObservationSequencesReader
					        .readSequences(new ObservationVectorReader(), testReader);
				
		        testReader.close();
		        
		        short gesture; // punch = 1, scrolldown = 2, send = 3
		        double punchProbability, scrolldownProbability, sendProbability;
		        for (int i = 0; i < testSequences.size(); i++) {
		       
		            punchProbability = learntHmmPunch.probability(testSequences
		                    .get(i));
		         
		            
		            line = line+"\n" + "Puch Probability is: " + punchProbability;
		           
		            
		        }
				} catch (IOException e) {
					// TODO Auto-generated catch block
					line=e.toString();
					e.printStackTrace();
				} catch (FileFormatException e) {
					// TODO Auto-generated catch block
					line=e.toString();
					e.printStackTrace();
				}
		
		
		return line;
    }
    
    
    
    @GET
    @Produces("application/x-javascript")
    @Path("HMMTesting/{filename:.+}")
    public String hbaseCreate(@QueryParam("callback") String callback, @PathParam("filename") String filename) {
        String line="";
        
       
		
		return line;
    }
  

    /**
     * PUT method for updating or creating an instance of Operation
     * @param content representation for the resource
     * @return an HTTP response with content of the updated or created resource.
     */
    @PUT
    @Consumes("application/json")
    public void putJson(String content) {
    }

}