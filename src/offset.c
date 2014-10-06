#include <stdio.h>
#include <string.h>
#include <math.h>
#include <malloc.h>

const int max_size=2000;
const int N=40;
const int max_w=50;

void ConvertUpper(char *vocab)
{
  int a;
  for (a=0; a<max_w; a++) vocab[a]=toupper(vocab[a]);
}
void ConvertLower(char *vocab)
{
  int a;
  for (a=0; a<max_w; a++) vocab[a]=tolower(vocab[a]);
}

int main(int argc, char **argv)
{
    FILE *f;
    char st1[max_size], bestw[max_size], file_name[max_size],Wa[max_size],Wb[max_size],Wc[max_size];
    float dist, len, bestd,Y[max_size];
    int words, size, a, b, c, d,i,j,k,flag=0,T,unkCount=0,totalUnk=0;
    float *M;
    char *vocab;
    if (argc<3) {
      //	printf("Usage: ./offset <FILE> <Wa> <Wb> <Wc>>\nwhere FILE contains word projections\nW* are the words for Wb-Wa + Wc =? Wd\n output Wd closest word of Wc for given relation");
       printf("Usage: ./offset <FILE> <TEST_FILE>");
	return 0;
    }

    strcpy(file_name, argv[1]);
    sscanf (argv[3],"%d",&T);

    f=fopen(file_name, "rb");
    if (f==NULL) {printf("Input file not found\n"); return -1;}
    fscanf(f, "%d", &words);
    fscanf(f, "%d", &size);

    vocab=(char *)malloc(words*max_w*sizeof(char));
    M=(float *)malloc(words*size*sizeof(float));


    if (M==NULL) {
        printf("Cannot allocate memory: %d MB\n", words*size*sizeof(float)/1048576); 
        return -1;
    }
    //    fprintf(stderr,"SuCCESS-3!\n");
    for (b=0; b<words; b++) {
        fscanf(f, "%s", &vocab[b*max_w]);
        for (a=0; a<size; a++) fscanf(f, "%f", &M[a+b*size]);
	strcpy(bestw,&vocab[b*max_w]);
	//       	fprintf(stderr,"%d %s\n",b,bestw);

	len=0;
	for (a=0; a<size; a++) len+=M[a+b*size]*M[a+b*size];
	len=sqrt(len);
	for (a=0; a<size; a++) M[a+b*size]/=len;
    }
    //   fprintf(stderr,"SuCCESS-4!\n");

    for (a=0; a<words*max_w; a++) vocab[a]=toupper(vocab[a]);
    fclose(f);
    fprintf(stderr,"Embeddings are read!\n");

    f=fopen(argv[2], "rb");
    if (f==NULL) {printf("Input file not found\n"); return -1;}

    for(k =0;k<T;k++){
      fscanf(f,"%s %s %s",Wa,Wb,Wc);
      if(k%400 == 0)
	fprintf(stderr,"-");

      ConvertUpper(Wa);
      ConvertUpper(Wb);
      ConvertUpper(Wc);
      flag = 0;
      for (a=0; a<words; a++) if (!strcmp(&vocab[a*max_w], Wa)) break;
      if (a==words)
	{
	  //	  printf("Wa Word %s was not found in dictionary\n",Wa);
	  flag =1;
	  unkCount++;
	  //	  return -1;
	}

      for (b=0; b<words; b++) if (!strcmp(&vocab[b*max_w], Wb)) break;
      if (b==words){
	//	printf("Wb Word %s was not found in dictionary\n",Wb);
	flag = 1;
	unkCount++;
	//	return -1;
      }

      for (c=0; c<words; c++) if (!strcmp(&vocab[c*max_w], Wc)) break;
      if (c==words){
	//	printf("Wc Word %s was not found in dictionary\n",Wc);
	flag = 1;
	unkCount++;
	//	return -1;
      }
      if(flag == 1)
	{
	  totalUnk++;
	  ConvertLower(Wa);
	  ConvertLower(Wb);
	  ConvertLower(Wc);
	  printf("%s\t%s\t%s\tUNKNOWN\n",Wa,Wb,Wc);
	  continue;
	}

      for (i=0; i<size; i++)Y[i]=M[i+b*size]+M[i+c*size]-M[i+a*size];

      len=0;
      for (i=0; i<size; i++) len+=Y[i]*Y[i];
      len=sqrt(len);
      for (i=0; i<size; i++) Y[i]/=len;

      bestd = 0;
      for(i=0; i<words; i++){
	dist=0;
	for (j=0; j<size; j++)dist+=M[j+i*size]*Y[j];
	if (dist>bestd && strcmp(&vocab[i*max_w], Wc) && strcmp(&vocab[i*max_w], Wb) && strcmp(&vocab[i*max_w], Wa) )
	  {
	    bestd=dist;
	    strcpy(bestw, &vocab[i*max_w]);
	  }
      }

    //    for (i=0; i<max_w; i++) bestw[i]=tolower(bestw[i]);
    ConvertLower(Wa);
    ConvertLower(Wb);
    ConvertLower(Wc);
    ConvertLower(bestw);
    printf("%s\t%s\t%s\t%s\n",Wa,Wb,Wc,bestw);
    }
    /*
    printf("Enter word (EXIT to terminate): ");
    scanf("%s", st1);

    for (a=0; a<strlen(st1); a++) st1[a]=toupper(st1[a]);
    printf("%s ",st1);

    for (b=0; b<words; b++)if (!strcmp(&vocab[b*max_w], st1)) break;
    if (b==words) printf("Word was not found in dictionary\n");

    dist = 0;
    for (j=0; j<size; j++) dist+=M[j+b*size]*Y[j];
    printf("%f\n",dist);
    */
    fprintf( stderr, "\n #of unknowns %d\n number of lines containing unknowns %d",unkCount,totalUnk);
    return 0;
}
