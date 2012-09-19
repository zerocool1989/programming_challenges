
import java.util.*;
import java.io.*;

public class Erdos {
	public String start = "Erdos, P";
	
	
	public ArrayList<String> split(String paper){
		ArrayList<String> returnval = new ArrayList<String>();
		String [] local = paper.split(".:");
		String [] authors = local[0].split("\\.,");
		for(String author: authors){
			returnval.add(author.trim());
		}
		return returnval;
	}
	
	public void execute(){
		int scenarios,P,N;
		Scanner scan = null ;
		try {
			scan = new Scanner(new File("erdos.txt"));
		} catch (FileNotFoundException e) {
			System.out.println("Unable to open file");
			e.printStackTrace();
		}
		
		scenarios = Integer.parseInt(scan.nextLine().trim());
		String [] papers = scan.nextLine().split(" ");
		P = Integer.parseInt(papers[0]);
		N = Integer.parseInt(papers[1]);
		
		System.out.println(scenarios);
		System.out.println(P);
		System.out.println(N);
		String paper;
		while(scenarios-- >0){
			HashMap <String,HashSet<String> > graph =  new HashMap<String,HashSet<String> > ();
			do{
	            paper = scan.nextLine();
	            ArrayList<String> authors = null;
	            if (paper!="")
	                authors = split(paper);
	            // now authors has the list of authors for the particular paper
	            //constructing the graph
	            for(String author : authors){
	            	HashSet<String> s = new HashSet<String>();
	            	for(String author1 : authors){
	            		if(!author1.equals(author)){
	            			s.add(author1);
	            			
	            		}
	            	}
	            	if(graph.containsKey(author)){
	            		HashSet<String> s1 = new HashSet<String>();
	            		s1 = graph.get(author);
	            		for(String author1 : authors){
		            		if(!author1.equals(author)){
		            			s1.add(author1);
		            			
		            		}
		            	}
	            		graph.put(author, s1);
	            	}
	            	else{
	            		graph.put(author, s);
	            	}
	            		
	            }
	        
	        }while(--P>0);
			
			//now that we have the graph run bfs with starting node as Erdos, P
			//printgraph(graph);
			runBFS(graph);	
		}
	}
	
	public void runBFS(HashMap <String,HashSet<String> > graph){
		
        HashMap<String,String> color =  new HashMap<String,String>();
        HashMap<String,Integer > distance = new HashMap<String , Integer >();
        for(String s: graph.keySet()){
        	if (s.equals(start)){
        		continue;
        	}
        	else{
        		color.put(s,"WHITE");
        		distance.put(s, -1);
        	}
        }
        color.put(start,"BLACK");
        distance.put(start, 0);
        LinkedList<String> list = new LinkedList<String>();
        list.add(start);
        /*
         * while(!Q.empty()){
            string next=Q.front();
            Q.pop();
            for(its=graph[next].begin();its!=graph[next].end();its++){
                if (color[(*its)]=="WHITE"){
                    color[(*its)]="BLACK";
                    distance[(*its)]=distance[next]+1;
                    Q.push((*its));
                }
            }
            color[next]="BLACK";
        }
         */
        
        while(!list.isEmpty()){
        	String next = list.removeLast();
        	for(String str:graph.get(next)){
        		if (color.get(str).equals("WHITE")){
        			color.put(str, "BLACK");
        			distance.put(str, distance.get(next)+1);
        			list.add(str);
        		}
        	}
        	color.put(next, "BLACK");
        }
        
        for(String str:distance.keySet()){
        	System.out.println(str +"   "+ distance.get(str));
        }
        
	}
	
	
	public void printgraph(HashMap <String,HashSet<String> > graph){
		for(String s : graph.keySet()){
			System.out.print(s);
			System.out.print(" ");
			for(String s1 : graph.get(s)){
				System.out.print(s1);
				System.out.print("  ");
			}
			System.out.println();
		}
	}
}
