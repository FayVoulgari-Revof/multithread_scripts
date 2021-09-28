#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#define N 8000


int main(){
	//arxikopoihsh-dhlwsh metablhtwn
	int i,tmp;
	int tmp1=0;
	int tmp2=0;
	int tmp3=0;
	int tmp4=0;
	int sum=0;
	//pinakas poy tha apothikeysoyme ta apotelesmata toy fork gia thn anagnwrish twn child kai parent
    pid_t pid[4];

	//oi 4 pinakes poy pairnei ws orisma h synarthsh pipe kai tha xrhsimopoihthoun gia thn epikoinwnia twn diergasiwn 
  int fd[2];
  int fe[2];
  int ff[2];
  int fh[2];
//xrhsimopoioyme swlinosh gia thn epikoinwnia twn diergasiwn
  pipe(fh);
  pipe(fd);
  pipe(fe);
  pipe(ff);
//dhmioyrgoyntai ta 4 child 
    for (i=0;i<4;i++) {
        pid[i] = fork();
        if (pid[i] == 0) { // break an einai child 
            break;
        }
    }


	if(pid[0] == 0){//prwto child mpainei se aythn thn if
		close(fd[0]);//kleinoyme to read afoy den tha diabasei h diergasia apo ton parent
		for(int j=0;j<N/4;j++){
			tmp1+=j;
			}
		write(fd[1], &tmp1, sizeof(tmp1)); //grafoyme to athroisma poy ypologise wste na to diabasei o parent
		close(fd[1]);//kleinoyme thn write afoy teliwsame me to athroisma
		exit(0);//exodos apo thn diergasia
	}

	if(pid[1] == 0){
		close(fe[0]);
		for(int x=N/4;x < N/2;x++){
			tmp2+=x;
		}
		write(fe[1], &tmp2, sizeof(tmp2));
		close(fe[1]);

		exit(0);
	}
	if(pid[2] == 0){
		close(fh[0]);
		for(int h=N/2;h<3*N/4;h++){
			tmp3 += h;
			}
		write(fh[1], &tmp3, sizeof(tmp3));
		close(fh[1]);

		exit(0);
	}
	if(pid[3] == 0){
		close(ff[0]);
		for(int w=3*N/4;w<=N;w++){
			tmp4+=w;

		}
		write(ff[1], &tmp4, sizeof(tmp4));
		close(ff[1]);
		exit(0);
	}

	if (pid[0] != 0 && pid[1] != 0 && pid[2] != 0 && pid[3] != 0) {//mpainei o parent se aythn thn if 

		close(fh[1]);//kleinoyme ta pipes gia to write afoy den tha grapsei kati 
		close(fe[1]);
		close(fd[1]);
		close(ff[1]);

        for(i=0;i<4;i++) {
            wait(&tmp);//perimenoyme na teliwsoyn prwta oi diergasies child
        }

		read(fd[0], &tmp1, sizeof(tmp1));//diavazoyme tis times poy exoyn grapsei ta child sto pipeline
		read(fh[0], &tmp3, sizeof(tmp3));
		read(fe[0], &tmp2, sizeof(tmp2));
		read(ff[0], &tmp4, sizeof(tmp4));


		close(fh[0]);//kleinoyme kai to read kommati
		close(fe[0]);
		close(fd[0]);
		close(ff[0]);
		
		sum=tmp1+tmp2+tmp3+tmp4; //ypologizoyme to athroisma 

	}

	 printf("%d\n",sum);
	 return 0;
}
