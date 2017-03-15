#include<stdio.h>
#include<conio.h>
#include<dos.h>
#include<graphics.h>

union REGS in,out;

void initmouse(void)
	{
		in.x.ax = 0;
		int86(51,&in,&out);
		if(out.x.ax == 0)
			{
				printf("\nmouse driver not loaded!");

			}
		in.x.ax = 1;
		int86(51,&in,&out);

		in.x.ax = 7;
		in.x.cx = 0;
		in.x.dx = getmaxx();
		int86(51,&in,&out);

		in.x.ax = 8;
		in.x.cx = 0;
		in.x.dx = (getmaxy()/2);
		int86(51,&in,&out);

	}
	void mouseread(int *a,int *b,int *c)
		{
			in.x.ax = 3;
			int86(51,&in,&out);
			*a = out.x.cx;
			*b = out.x.dx;
			*c = out.x.bx;
		}

	void polygon(int x[],int y[],int c)
		{
			int i;

			for(i=0;i<c;i++)
				{
					if(i!=c-1)
						{
							line(x[i],y[i],x[i+1],y[i+1]);
						}
					else
						{
							line(x[i],y[i],x[0],y[0]);
						}
				}
		}

	void main()

		{
			int gd,gm;
			int x,y,b,flag=0;
			int xc[100],yc[100],i;

			gd = DETECT;
			initgraph(&gd,&gm,"C:\\TurboC3\\bgi");

			initmouse();
			i = 0;

			do
			    {
				mouseread(&x,&y,&b);

				if((b & 0x1) && (flag==0))

					{
						xc[i] = x;
						yc[i] = y;
						i++;
						flag = 1;
						putpixel(x-1,y-1,15);
					}
				if(b==0 && flag==1)
					flag = 0;
			    } while(!(b &0x2));

			    in.x.ax = 2;
			    int86(51,&in,&out);
			    polygon(xc,yc,i);
			    delay(5000);
			    closegraph();
			    printf("\npress any key to exit:");
			    getch();

		}
