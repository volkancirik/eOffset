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
    char st1[max_size], bestw[max_size], file_name[max_size],Wa[max_size],Wb[max_size],Sim[max_size];
    float dist, len, bestd,Y[max_size];
    int words, size, a, b, c, d,i,j,k,flag=0;
    float *M;
    char *vocab;
    if (argc!=3) {
       printf("Usage: ./wordsim <EMBEDING FILE> <TEST_FILE>");
	return 0;
    }

    strcpy(file_name, argv[1]);

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


    for (a=0; a<words*max_w; a++) vocab[a]=toupper(vocab[a]);
    fclose(f);
    fprintf(stderr,"Embeddings are read!\n");

    f=fopen(argv[2], "rb");
    if (f==NULL) {printf("Input file not found\n"); return -1;}

    for(k =0;k<354;k++){
      fscanf(f,"%s %s %s",Wa,Wb,Sim);
      if(k%20 == 0)
	fprintf(stderr,"-");

      ConvertUpper(Wa);
      ConvertUpper(Wb);
      flag = 0;
      for (a=0; a<words; a++) if (!strcmp(&vocab[a*max_w], Wa)) break;
      if (a==words)
	{
	  //	  printf("Wa Word %s was not found in dictionary\n",Wa);
	  flag =1;
	  //	  return -1;
	}

      for (b=0; b<words; b++) if (!strcmp(&vocab[b*max_w], Wb)) break;
      if (b==words){
	//	printf("Wb Word %s was not found in dictionary\n",Wb);
	flag = 1;
	//	return -1;
      }

      if(flag == 1)
	{
	  /*
	  ConvertLower(Wa);
	  ConvertLower(Wb);
	  printf("%s or%s\t%s\t0\n",Wa,Wb,Sim);
	  */
	  continue;
	}

      dist=0;
      for (j=0; j<size; j++)dist+=M[j+a*size]*M[j+b*size];
    ConvertLower(Wa);
    ConvertLower(Wb);
    printf("%s\t%s\t%s\t%.2f\n",Wa,Wb,Sim,dist);
    }
    return 0;
}
