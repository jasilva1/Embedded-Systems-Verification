//Josh Silva
//Lab 1 Part B

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reset(char *la, int num_elements) {
	int i;
	for(i = 0; i < num_elements; i++) {
		la[i] = '\0';
	}
}

int main(int argc, char * argv[]) {
	if (argc != 4) {
		fprintf(stderr, "Usage: %s <Verilog file> <Number of Transitions> <Target State>\n", argv[0]);
		return 1;
	}
	int n_reg=0;
	int num;
	int i;
	int fcount;
	int number_of_variables = 1;
	int number_of_clauses = 0;
	int reg_location[50] = {0};
	int newreg_location[50] = {0};
	int state[50] = {-1};
	char target[33];

	FILE *fptr;
	FILE *fnew;

	char u[3000];

	char writebuffer[100];
	reset(writebuffer,100);

	char writefilename[25];
	char outputfile[25];
	char *filename = argv[1];
	int n_transition = atoi(argv[2]);
	strncpy(target, argv[3], sizeof(target) - 1);
	target[sizeof(target) - 1] = '\0';

	char *dot = strrchr(filename, '.');
	if (dot && strcmp(dot, ".v") == 0) {
		*dot = '\0';
	}

	strcpy(writefilename,filename);
	strcat(writefilename,".cnf");

	strcpy(outputfile,filename);
	strcat(outputfile,".output");

	strcat(filename,".v");
	fptr = fopen(filename, "r");

	if(fptr == NULL) {
		printf("\nRead Error\n");
		return(-1);
	}

	fnew = fopen(writefilename, "w");

	if (fnew == NULL) {
		printf("Write Error");
        	exit(1);
    	}
	fprintf(fnew, "%s", "c Converted File: ");
	fprintf(fnew, "%s", filename);


	char variables[800][20];

	for (i = 0; i<800; i++) {
		variables[i][0]	= '\0';
	}


	reset(u,3000);
	//Input
	while( fgets(u, 3000, fptr) != NULL ) {
		if (u[0] == 'i' && u[1] == 'n' && u[2]== 'p' && u[3]== 'u' && u[4]== 't') {
			int i;
			for (i = 0; i <3000; i++) {
				if (u[i] == ' ') {
					num = i+1;
				}
				else if (u[i] == ',') {
					int counter=0;
					while(num<i) {
						variables[number_of_variables][counter] = u[num];
						counter++;
						variables[number_of_variables][counter] = '\0';
						num++;
					}
					num = i+1;
					number_of_variables ++;
				}
				else if (u[i] == ';') {
					int counter=0;
					while(num<i) {
						variables[number_of_variables][counter] = u[num];
						counter++;
						variables[number_of_variables][counter] = '\0';
						num++;
					}
					num = i+1;
					number_of_variables ++;
				}
			}
		}

		//Output
		else if (u[0] == 'o' && u[1] == 'u' && u[2]== 't' && u[3]== 'p' && u[4]== 'u' && u[5]== 't') {
			int i;
			for (i = 0; i <3000; i++) {
				if (u[i] == ' ') {
					num = i+1;
				}
				else if (u[i] == ',') {
					int counter=0;
					while(num<i) {
						variables[number_of_variables][counter] = u[num];
						counter++;
						variables[number_of_variables][counter] = '\0';
						num++;
					}
					num = i+1;
					number_of_variables ++;
				}
				else if (u[i] == ';') {
					int counter=0;
					while(num<i) {
						variables[number_of_variables][counter] = u[num];
						counter++;
						variables[number_of_variables][counter] = '\0';
						num++;
					}
					num = i+1;
					number_of_variables ++;
				}
			}
		}

		//Wire
		else if (u[0] == 'w' && u[1] == 'i' && u[2]== 'r' && u[3]== 'e') {
			int i;
			for (i = 0; i <3000; i++) {
				if (u[i] == ' ') {
					num = i+1;
				}
				else if (u[i] == ',') {
					int counter=0;
					while(num<i) {
						variables[number_of_variables][counter] = u[num];
						counter++;
						variables[number_of_variables][counter] = '\0';
						num++;
					}
					num = i+1;
					number_of_variables ++;
				}
				else if (u[i] == ';') {
					int counter=0;
					while(num<i) {
						variables[number_of_variables][counter] = u[num];
						counter++;
						variables[number_of_variables][counter] = '\0';
						num++;
					}
					num = i+1;
					number_of_variables ++;
				}
			}
		}

		//Reg
		else if (u[0] == 'r' && u[1] == 'e' && u[2]== 'g') {
			int i;
			for (i = 0; i <3000; i++) {
				if (u[i] == ' ') {
					num = i+1;
				}
				else if (u[i] == ',') {
					int counter=0;
					while(num<i) {
						variables[number_of_variables][counter] = u[num];
						counter++;
						variables[number_of_variables][counter] = '\0';
						num++;
					}
					num = i+1;
					reg_location[n_reg] = number_of_variables;
					number_of_variables ++;
					n_reg++;
				}
				else if (u[i] == ';') {
					int counter=0;
					while(num<i) {
						variables[number_of_variables][counter] = u[num];
						counter++;
						variables[number_of_variables][counter] = '\0';
						num++;
					}
					num = i+1;
					reg_location[n_reg] = number_of_variables;
					number_of_variables ++;
					n_reg++;
				}
			}
		}
		//Counting AND clauses
		else if (u[0] == 'a' && u[1] == 'n' && u[2]== 'd') {
			number_of_clauses = number_of_clauses + (3*n_transition);
		}
		// Counting NOTclauses
		else if (u[0] == 'n' && u[1] == 'o' && u[2]== 't') {
			number_of_clauses = number_of_clauses + (2*n_transition);
		}
	reset(u,3000);
	}

	int n_var;
	n_var = (number_of_variables-1) * n_transition;
	int nclause = 0;

	nclause = ((n_transition-1)*n_reg)*2;

	nclause = number_of_clauses + nclause+n_reg+n_reg;

	printf("\nVariables: %d\n",n_var);
	printf("Clauses: %d\n\n",nclause);

	fprintf(fnew, "%s", "\nc");
	fprintf(fnew, "%s", "\nc Variables: ");
	sprintf(writebuffer, "%i", n_var);
	fprintf(fnew, "%s", writebuffer);
	reset(writebuffer,100);
	fprintf(fnew, "%s", "\nc Clauses: ");
	sprintf(writebuffer, "%i", nclause);
	fprintf(fnew, "%s", writebuffer);
	reset(writebuffer,100);

	//Printing the variable list
	fprintf(fnew, "%s", "\nc Variable List:");
	for(i=1; i<number_of_variables ; i++) {

			fprintf(fnew, "%s", "\nc   ");
			int ncount = 0;
			while(ncount < n_transition)
			{
				int multiples;
				multiples = ((number_of_variables-1)*ncount)+i;

				printf("%i",multiples);

				reset(writebuffer,100);
				sprintf(writebuffer, "%i", multiples);
				fprintf(fnew, "%s", writebuffer);

				if(multiples < 10){
				fprintf(fnew, "%s", "     ");
				printf("     ");
				}
				else if(multiples < 100){
				fprintf(fnew, "%s", "    ");
				printf("    ");
				}
				else if(multiples < 1000){
				fprintf(fnew, "%s", "   ");
				printf("   ");
				}

				fprintf(fnew, "%s", "; ");
				ncount++;
			}

			fprintf(fnew, "%s", variables[i]);

			printf("%s\n",variables[i]);
	}

	fprintf(fnew, "%s", "\nc\np cnf ");
	sprintf(writebuffer, "%i", n_var);
	fprintf(fnew, "%s", writebuffer);
	reset(writebuffer,100);
	fprintf(fnew, "%s", " ");

	sprintf(writebuffer, "%i", nclause);

	fprintf(fnew, "%s", writebuffer);
	reset(writebuffer,100);
	fprintf(fnew, "%s", "\nc Initial States\n");


	//Setting the Iitial Statrs
	for (i=0;i<n_reg;i++){
		fprintf(fnew, "%s", "-");
		sprintf(writebuffer, "%i", reg_location[i]);
		fprintf(fnew, "%s", writebuffer);
		reset(writebuffer,100);
		fprintf(fnew, "%s", " 0\n");
	}
	fprintf(fnew, "%s", "c");
	fclose(fptr);

	fptr = fopen(filename, "r");
	reset(u,3000);

	//Scanning gates
	//writing file
	while( fgets(u, 3000, fptr) != NULL ) {
		if (u[0] == 'a' && u[1] == 'n' && u[2]== 'd') {
			int out, in0,in1;
			char currentVariable[20];
			currentVariable[0] = '\0';

			int i;
			for (i = 0; i <3000; i++) {

				if (u[i] == '(') {
					num = i+1;
					out = number_of_variables+1;
				}

				else if (u[i] == ',') {
					currentVariable[0] = '\0';
					int counter=0;

					while(num<i) {
						currentVariable[counter] = u[num];
						counter++;
						currentVariable[counter] = '\0';
						num++;
					}
					num = i+1;

					char nums;
					int k;
					for(k=0; k<number_of_variables ; k++)	{
						nums = 0;

						while(nums<21){
							if (currentVariable[nums] == variables[k][nums]) {
								nums++;
								if (currentVariable[nums] == '\0' && variables[k][nums] == '\0'){
									nums = 25;
									if (out == number_of_variables+1){
										out = k;
									}
									in0 = k;
									k = number_of_variables+1;
								}
							}

							else {
								nums = 25;
							}
						}
					}
				}


				else if (u[i] == ')') {
					currentVariable[0] = '\0';
					int counter=0;
					while(num<i) {
						currentVariable[counter] = u[num];
						counter++;
						currentVariable[counter] = '\0';
						num++;
					}
					num = i+1;

					char nums;
					int k;
					for(k=0; k<number_of_variables ; k++){
						nums = 0;
						while(nums<21){
							if (currentVariable[nums] == variables[k][nums]) {
								nums++;
								if (currentVariable[nums] == '\0' && variables[k][nums] == '\0'){
									nums = 23;
									in1 = k;
									k = number_of_variables+1;
								}
							}

							else {
								nums = 21;
							}
						}
					}
				}
			}

			//DIMACS
			int ncount = 0;
			while(ncount < n_transition) {
				fprintf(fnew, "%s", "\nc ");
				fprintf(fnew, "%s", u);

				reset(writebuffer,100);
				sprintf(writebuffer, "%i",in0);
				fprintf(fnew, "%s", writebuffer);
				fprintf(fnew, "%s", " -");
				reset(writebuffer,100);
				sprintf(writebuffer, "%i", out);
				fprintf(fnew, "%s", writebuffer);
				reset(writebuffer,100);
				fprintf(fnew, "%s", " 0\n");

				sprintf(writebuffer, "%i", in1);
				fprintf(fnew, "%s", writebuffer);
				fprintf(fnew, "%s", " -");
				reset(writebuffer,100);
				sprintf(writebuffer, "%i", out);
				fprintf(fnew, "%s", writebuffer);
				reset(writebuffer,100);
				fprintf(fnew, "%s", " 0\n-");

				sprintf(writebuffer, "%i", in0);
				fprintf(fnew, "%s", writebuffer);
				fprintf(fnew, "%s", " -");
				reset(writebuffer,100);
				sprintf(writebuffer, "%i", in1);
				fprintf(fnew, "%s", writebuffer);
				fprintf(fnew, "%s", " ");
				reset(writebuffer,100);
				sprintf(writebuffer, "%i", out);
				fprintf(fnew, "%s", writebuffer);
				reset(writebuffer,100);

				fprintf(fnew, "%s", " 0\nc");

				ncount++;

				in0 = ((number_of_variables-1) ) + in0;
				in1 = ((number_of_variables-1) ) + in1;
				out = ((number_of_variables-1) ) + out;
			}
		}
		//NOT gate
		//mapping
		else if (u[0] == 'n' && u[1] == 'o' && u[2]== 't') {
			int out, in;
			char currentVariable[20];
			currentVariable[0] = '\0';

			int i;
			for (i = 0; i <3000; i++) {

				if (u[i] == '(') {
					num = i+1;
				}

				else if (u[i] == ',') {
					currentVariable[0] = '\0';
					int counter=0;
					while(num<i) {
						currentVariable[counter] = u[num];
						counter++;
						currentVariable[counter] = '\0';
						num++;
					}
					num = i+1;
					char nums;
					int k;
					for(k=0; k<number_of_variables ; k++)	{
						nums = 0;
						while(nums<20){
							if (currentVariable[nums] == variables[k][nums]) {
								nums++;
								if (currentVariable[nums] == '\0' && variables[k][nums] == '\0'){
									nums = 21;
									out = k;
									k = number_of_variables+1;
								}
							}

							else {
								nums = 21;
							}
						}
					}

				}

				else if (u[i] == ')') {
					currentVariable[0] = '\0';
					int counter=0;
					while(num<i) {
						currentVariable[counter] = u[num];
						counter++;
						currentVariable[counter] = '\0';
						num++;
					}
					num = i+1;

					char nums;
					int k;
					for(k=0; k<number_of_variables ; k++){
						nums = 0;
						while(nums<20){
							if (currentVariable[nums] == variables[k][nums]) {
								nums++;
								if (currentVariable[nums] == '\0' && variables[k][nums] == '\0'){
									nums = 21;
									in = k;
									k = number_of_variables+1;
								}
							}

							else {
								nums = 21;
							}
						}
					}

				}
			}
			//dimacs
			int ncount = 0;
			while(ncount < n_transition) {

				fprintf(fnew, "%s", "\nc ");
				fprintf(fnew, "%s", u);
				fprintf(fnew, "%s", "-");

				reset(writebuffer,100);
				sprintf(writebuffer, "%i", in);
				fprintf(fnew, "%s", writebuffer);
				fprintf(fnew, "%s", " -");
				reset(writebuffer,100);
				sprintf(writebuffer, "%i", out);
				fprintf(fnew, "%s", writebuffer);
				reset(writebuffer,100);
				fprintf(fnew, "%s", " 0\n");

				sprintf(writebuffer, "%i", in);
				fprintf(fnew, "%s", writebuffer);
				fprintf(fnew, "%s", " ");
				reset(writebuffer,100);
				sprintf(writebuffer, "%i", out);
				fprintf(fnew, "%s", writebuffer);
				reset(writebuffer,100);
				fprintf(fnew, "%s", " 0\nc");
				ncount++;

				in = ((number_of_variables-1) ) + in;
				out = ((number_of_variables-1)) + out;
			}
		}
		//counting target states
		else if (argv[3] != '\0') {
			fcount = 0;
			int t_length = strlen(argv[3]);
			for(int i = 0; i < t_length; i++) {
				if(argv[3][i] == '1' || argv[3][i]== '0'){
					fcount++;
				}
			}

			//printf("\nNumber of Target States : %d\n",fcount);////////////////////////

			//assigning target state values
			int f;
		 	f = fcount;
			i=0;
			while( i < fcount ){
				if(argv[3][i] == '0'){
					state[f-1] = 0;
				}
				else if(argv[3][i] == '1'){
					state[f-1] = 1;
				}
				else{
					printf("Target State Error");
					return(-1);
				}
				f--;
				i++;
			}
			i = 0;
			while( i < fcount ){
				//printf("S%d : %d \n",i,state[i]);///////////////////
				i++;
			}
		}
			reset(u,3000);
}

	int s;
	for (i=0; i < n_reg; i++){
		reset(writebuffer,100);
		writebuffer[0]='N';

		for (s=0; s<20; s++){
			writebuffer[s+1] =  variables[reg_location[i]][s];
			writebuffer[s+2] = '\0';
		}
		char nums;
		int k;
		for(k=0; k<number_of_variables ; k++){
			nums = 0;
			while(nums<20){
				if (writebuffer[nums] == variables[k][nums]) {
					nums++;
					if (writebuffer[nums] == '\0' && variables[k][nums] == '\0'){
						newreg_location[i] = k;
						nums = 21;
					}
				}

				else {
					nums = 21;
				}
			}
		}
	}

	for (i=0; i < n_reg; i++){
		int ncount = 0;
		int in = newreg_location[i] + (number_of_variables-1);

		int out = reg_location[i];

		while(ncount < n_transition-1)
		{
		  	printf("In: %d Out: %d \n",in,out);
			//writing transition buffers
			fprintf(fnew, "%s", "\nc Transition Buffer\n");
			fprintf(fnew, "%s", "-");

			reset(writebuffer,100);
			sprintf(writebuffer, "%i", out);
			fprintf(fnew, "%s", writebuffer);
			fprintf(fnew, "%s", " ");
			reset(writebuffer,100);
			sprintf(writebuffer, "%i", in);
			fprintf(fnew, "%s", writebuffer);
			reset(writebuffer,100);
			fprintf(fnew, "%s", " 0\n");

			sprintf(writebuffer, "%i", out);
			fprintf(fnew, "%s", writebuffer);
			fprintf(fnew, "%s", " -");
			reset(writebuffer,100);
			sprintf(writebuffer, "%i", in);
			fprintf(fnew, "%s", writebuffer);
			reset(writebuffer,100);
			fprintf(fnew, "%s", " 0\nc");

		  	in = in + (number_of_variables-1);
			out = out + (number_of_variables-1);
			ncount++;
		}
	}

	fprintf(fnew, "%s", "\nc Target State ");

	for (i=0; i <fcount; i++){
		reset(writebuffer,100);
		writebuffer[0]='N';
		writebuffer[1]='S';
		if (i<10){
			writebuffer[2] = i+'0';
			writebuffer[3] = '\0';
		}
		else if(i<100){
			int u;
			u = i/10;
			writebuffer[2] = u+'0';
			u = u*10;
			u = i - u;
			writebuffer[3] = u+'0';
			writebuffer[4] = '\0';
		}

		char nums;
		int k;
		for(k=0; k < number_of_variables ; k++){
			nums = 0;
			while(nums<20){
				if (writebuffer[nums] == variables[k][nums]) {
					nums++;
					if (writebuffer[nums] == '\0' && variables[k][nums] == '\0'){

						if (state[i]==0){
							fprintf(fnew, "%s", "\n");
							fprintf(fnew, "%s", "-");
							char abuffer[20];
							reset(abuffer,20);
							sprintf(abuffer, "%i", k +((n_transition-1)*(number_of_variables-1)));
							fprintf(fnew, "%s", abuffer);
							fprintf(fnew, "%s", " 0");
						}
						else if (state[i]==1){
							fprintf(fnew, "%s", "\n");
							char abuffer[20];
							reset(abuffer,20);
							sprintf(abuffer, "%i", k+((n_transition-1)*(number_of_variables-1)));
							fprintf(fnew, "%s", abuffer);
							fprintf(fnew, "%s", " 0");
						}
						else{
							printf("State error");
						}
						nums = 21;
					}
				}

				else {
					nums = 21;
				}
			}
		}
	}
	fclose(fptr);
	fclose(fnew);

	//char pico[2];
	char command[50];
	reset(command,50);
	printf("\nVerilog converted to  Dimacs Successfully\n");
	printf("Calling PicoSat\n");
	//printf("Would you like to see every satisifiable condition set? (y or n): ");
        //scanf("%1s", pico);
	//if (pico != "y" || pico != "n"){
	//	printf("\nEnter y or n.\n");
	//}
	//else if (pico == "y") {
	//	strcat(command,"picosat --all ");
        //	strcat(command,writefilename);
        //	strcat(command," > ");
        //	strcat(command,outputfile);
	//}
	//else if (pico == "n"){
	strcat(command,"picosat ");
	strcat(command,writefilename);
	strcat(command," > ");
	strcat(command,outputfile);
	//}
	system(command);
	reset(command,50);

	strcat(command,"cat ");
	strcat(command,outputfile);
	printf("\nCommand Called to picosat:\npicosat %s > %s \n",writefilename,outputfile);
	printf("\nTarget Variables:\n");
	i = 0;
	while( i < fcount ){
			printf("S%d : %d  ",i,state[i]);
			if (i%10 == 0){
				printf("\n");
			}
			i++;
		}
	printf("\n\nOutput File Contents: %s\n",outputfile);
	system(command);
	//printf("\n\nEND OF PROGRAM\n");
	return 0;
}
