#include <stdio.h>
#define MAX 20

typedef struct { int id, at, bt, priority; } Process;
typedef struct { int id, start, end; } Segment;

void metrics(Process p[], int n, int ct[]) {
    double sw=0, st=0; int i;
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for(i=0;i<n;i++) { int tat=ct[p[i].id]-p[i].at, wt=tat-p[i].bt;
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",p[i].id,p[i].at,p[i].bt,ct[p[i].id],tat,wt); sw+=wt; st+=tat; }
    printf("Average waiting time: %.2f\nAverage turnaround time: %.2f\n",sw/n,st/n);
}
void gantt(Segment g[], int k) { int i; printf("\nGantt chart:\n|"); for(i=0;i<k;i++) printf(" P%d |",g[i].id); printf("\n%d",g[0].start); for(i=0;i<k;i++) printf("\t%d",g[i].end); puts(""); }
void fcfs(Process p[],int n) {
 Process q[MAX],t; int ct[MAX]={0},i,j,time=0; Segment g[MAX];
 for(i=0;i<n;i++) q[i]=p[i];
 for(i=0;i<n-1;i++) for(j=i+1;j<n;j++) if(q[j].at<q[i].at){t=q[i];q[i]=q[j];q[j]=t;}
 for(i=0;i<n;i++){if(time<q[i].at)time=q[i].at;g[i].id=q[i].id;g[i].start=time;time+=q[i].bt;g[i].end=time;ct[q[i].id]=time;}
 puts("\n=== FCFS ===");gantt(g,n);metrics(p,n,ct);
}
void nonpreemptive(Process p[],int n,int mode) {
 int done[MAX]={0},ct[MAX]={0},time=0,finished=0,i,best; Segment g[MAX]; int k=0;
 while(finished<n){best=-1;for(i=0;i<n;i++)if(!done[i]&&p[i].at<=time){
   if(best==-1 || (mode==1 && (p[i].bt<p[best].bt || (p[i].bt==p[best].bt&&p[i].at<p[best].at))) || (mode==2 && (p[i].priority<p[best].priority || (p[i].priority==p[best].priority&&p[i].at<p[best].at)))) best=i; }
  if(best==-1){int next=-1;for(i=0;i<n;i++)if(!done[i]&&(next==-1||p[i].at<p[next].at))next=i;time=p[next].at;continue;}
  g[k].id=p[best].id;g[k].start=time;time+=p[best].bt;g[k].end=time;ct[p[best].id]=time;done[best]=1;finished++;k++;
 }
 if(mode==1)puts("\n=== SJF (non-preemptive) ===");else puts("\n=== Priority (non-preemptive; smaller number = higher priority) ===");gantt(g,k);metrics(p,n,ct);
}
void rr(Process p[],int n,int quantum){
 int rem[MAX],ct[MAX]={0},added[MAX]={0},q[10000],front=0,rear=0,time=0,finished=0,i,j,next;Segment g[10000];int k=0;
 for(i=0;i<n;i++){rem[i]=p[i].bt;if(i==0||p[i].at<time)time=p[i].at;}
 while(finished<n){for(i=0;i<n;i++)if(!added[i]&&p[i].at<=time){q[rear++]=i;added[i]=1;}
  if(front==rear){next=-1;for(i=0;i<n;i++)if(!added[i]&&(next==-1||p[i].at<p[next].at))next=i;if(next==-1)break;time=p[next].at;continue;}
  i=q[front++];g[k].id=p[i].id;g[k].start=time;{int run=rem[i]<quantum?rem[i]:quantum;time+=run;rem[i]-=run;}g[k++].end=time;
  for(j=0;j<n;j++)if(!added[j]&&p[j].at<=time){q[rear++]=j;added[j]=1;}
  if(rem[i]>0)q[rear++]=i;else{ct[p[i].id]=time;finished++;}
 }
 printf("\n=== Round Robin (quantum %d) ===\n",quantum);gantt(g,k);metrics(p,n,ct);
}
int main(void){Process p[MAX];int n,i,ch,quantum;
 printf("CPU SCHEDULING SIMULATOR\nEnter number of processes (1-%d): ",MAX);
 if(scanf("%d",&n)!=1||n<1||n>MAX){puts("Invalid process count.");return 1;}
 for(i=0;i<n;i++){p[i].id=i;printf("\nP%d arrival time: ",i);if(scanf("%d",&p[i].at)!=1||p[i].at<0){puts("Arrival time must be >= 0.");return 1;}
  printf("P%d burst time: ",i);if(scanf("%d",&p[i].bt)!=1||p[i].bt<=0){puts("Burst time must be > 0.");return 1;}
  printf("P%d priority (smaller number = higher): ",i);if(scanf("%d",&p[i].priority)!=1||p[i].priority<0){puts("Priority must be >= 0.");return 1;}}
 do{printf("\n1.FCFS  2.SJF  3.Priority  4.Round Robin  5.Run all  0.Exit\nChoice: ");if(scanf("%d",&ch)!=1)return 1;
  switch(ch){case 1:fcfs(p,n);break;case 2:nonpreemptive(p,n,1);break;case 3:nonpreemptive(p,n,2);break;case 4:printf("Time quantum: ");if(scanf("%d",&quantum)!=1||quantum<=0){puts("Quantum must be > 0.");return 1;}rr(p,n,quantum);break;case 5:fcfs(p,n);nonpreemptive(p,n,1);nonpreemptive(p,n,2);printf("Time quantum: ");if(scanf("%d",&quantum)!=1||quantum<=0){puts("Quantum must be > 0.");return 1;}rr(p,n,quantum);break;case 0:puts("Goodbye.");break;default:puts("Invalid choice.");}}
 while(ch!=0);return 0;}
