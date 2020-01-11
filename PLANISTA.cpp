#include<windows.h>
#include<wchar.h>
#include<stdio.h>
#include<string.h>
#define size 50
#define Pre_emptive 0
#define Non_Pre_emptive 1
#define Clear_All 2
#define Auto_Fill 3
#define aging_value 2
#define _n_ 7
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
void AddControls(HWND);
void PE1();
void PE2();
void NPE1();
void NPE2();
void GetValues();
void AutoFill();
void ClearAll();
void AddMenus(HWND);
HWND P0AT, P0BT, P0P;
HWND P1AT, P1BT, P1P;
HWND P2AT, P2BT, P2P;
HWND P3AT, P3BT, P3P;
HWND P4AT, P4BT, P4P;
HWND P5AT, P5BT, P5P;
HWND P6AT, P6BT, P6P;
HWND PSL;
HMENU hMenu;
wchar_t buff[5];
char buffer[1000],temporary[100];
struct process
{
	int process_no;
	int AT;
	int BT;
	int P;
	int CT;
	int WT;
	int TAT;
	int RT;
	int BT_remaining;
	int init_scheduling;
}p[size], temp;
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow)
{
	MessageBox(NULL, "PLANISTA is a WIN32 application developed for analysing \"Aging\" as a solution to starvation (an issue associated with priority based scheduling algorithms).", "Welcome to PLANISTA", MB_OK);
	WNDCLASSW wc = { 0 };
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hInstance = hInst;
	wc.lpszClassName = L"PLANISTA_window_class";
	wc.lpfnWndProc = WindowProcedure;
	if (!RegisterClassW(&wc))
		return -1;
	CreateWindowW(L"PLANISTA_window_class", L"PLANISTA win32 application", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 50, 600, 750, NULL, NULL, NULL, NULL);
	MSG msg = { 0 };
	while (GetMessage(&msg, NULL, NULL, NULL))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}
LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_COMMAND:
		switch (wp)
		{
            case Clear_All: ClearAll();
                            break;
            case Auto_Fill: AutoFill();
                            break;
            case Pre_emptive:   PE1();
                                PE2();
                                break;
            case Non_Pre_emptive:   NPE1();
                                    NPE2();
                                    break;
		}
		break;
	case WM_CREATE: AddControls(hWnd);
                    AddMenus(hWnd);
		break;
	case WM_DESTROY:    PostQuitMessage(0);
		break;
	default:    return DefWindowProcW(hWnd, msg, wp, lp);
	}
}
void AddControls(HWND hWnd)
{
	//heading
	CreateWindowW(L"Static", L"PLANISTA", WS_VISIBLE | WS_CHILD | SS_CENTER, 0, 15, 600, 19, hWnd, NULL, NULL, NULL);
	//AT,BT,P
	CreateWindowW(L"Static", L"Arrival Time ( AT )", WS_VISIBLE | WS_CHILD, 100, 50, 120, 19, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Static", L"Burst Time ( BT )", WS_VISIBLE | WS_CHILD, 270, 50, 120, 19, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Static", L"Priority ( P )", WS_VISIBLE | WS_CHILD, 440, 50, 90, 19, hWnd, NULL, NULL, NULL);
	//P0
	CreateWindowW(L"Static", L"P0", WS_VISIBLE | WS_CHILD | SS_CENTER, 50, 100, 22, 22, hWnd, NULL, NULL, NULL);
	P0AT = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_CENTER, 149, 100, 22, 22, hWnd, NULL, NULL, NULL);
	P0BT = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_CENTER, 319, 100, 22, 22, hWnd, NULL, NULL, NULL);
	P0P = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_CENTER, 474, 100, 22, 22, hWnd, NULL, NULL, NULL);
	//P1
	CreateWindowW(L"Static", L"P1", WS_VISIBLE | WS_CHILD | SS_CENTER, 50, 140, 22, 22, hWnd, NULL, NULL, NULL);
	P1AT = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_CENTER, 149, 140, 22, 22, hWnd, NULL, NULL, NULL);
	P1BT = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_CENTER, 319, 140, 22, 22, hWnd, NULL, NULL, NULL);
	P1P = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_CENTER, 474, 140, 22, 22, hWnd, NULL, NULL, NULL);
	//P2
	CreateWindowW(L"Static", L"P2", WS_VISIBLE | WS_CHILD | SS_CENTER, 50, 180, 22, 22, hWnd, NULL, NULL, NULL);
	P2AT = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_CENTER, 149, 180, 22, 22, hWnd, NULL, NULL, NULL);
	P2BT = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_CENTER, 319, 180, 22, 22, hWnd, NULL, NULL, NULL);
	P2P = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_CENTER, 474, 180, 22, 22, hWnd, NULL, NULL, NULL);
	//P3
	CreateWindowW(L"Static", L"P3", WS_VISIBLE | WS_CHILD | SS_CENTER, 50, 220, 22, 22, hWnd, NULL, NULL, NULL);
	P3AT = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_CENTER, 149, 220, 22, 22, hWnd, NULL, NULL, NULL);
	P3BT = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_CENTER, 319, 220, 22, 22, hWnd, NULL, NULL, NULL);
	P3P = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_CENTER, 474, 220, 22, 22, hWnd, NULL, NULL, NULL);
	//P4
	CreateWindowW(L"Static", L"P4", WS_VISIBLE | WS_CHILD | SS_CENTER, 50, 260, 22, 22, hWnd, NULL, NULL, NULL);
	P4AT = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_CENTER, 149, 260, 22, 22, hWnd, NULL, NULL, NULL);
	P4BT = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_CENTER, 319, 260, 22, 22, hWnd, NULL, NULL, NULL);
	P4P = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_CENTER, 474, 260, 22, 22, hWnd, NULL, NULL, NULL);
	//P5
	CreateWindowW(L"Static", L"P5", WS_VISIBLE | WS_CHILD | SS_CENTER, 50, 300, 22, 22, hWnd, NULL, NULL, NULL);
	P5AT = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_CENTER, 149, 300, 22, 22, hWnd, NULL, NULL, NULL);
	P5BT = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_CENTER, 319, 300, 22, 22, hWnd, NULL, NULL, NULL);
	P5P = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_CENTER, 474, 300, 22, 22, hWnd, NULL, NULL, NULL);
	//P6
	CreateWindowW(L"Static", L"P6", WS_VISIBLE | WS_CHILD | SS_CENTER, 50, 340, 22, 22, hWnd, NULL, NULL, NULL);
	P6AT = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_CENTER, 149, 340, 22, 22, hWnd, NULL, NULL, NULL);
	P6BT = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_CENTER, 319, 340, 22, 22, hWnd, NULL, NULL, NULL);
	P6P = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_CENTER, 474, 340, 22, 22, hWnd, NULL, NULL, NULL);
	//Type of scheduling
	CreateWindowW(L"button", L"Pre-emptive", WS_VISIBLE | WS_CHILD, 100, 380, 175, 40, hWnd, (HMENU)Pre_emptive, NULL, NULL);
	CreateWindowW(L"button", L"Non-Pre-emptive", WS_VISIBLE | WS_CHILD, 355, 380, 175, 40, hWnd, (HMENU)Non_Pre_emptive, NULL, NULL);
	//PLANISTA SCHEDULE LOGGER
	CreateWindowW(L"Static", L"PLANISTA SCHEDULE LOGGER:", WS_VISIBLE | WS_CHILD | SS_CENTER, 0, 440, 600, 19, hWnd, NULL, NULL, NULL);
	PSL = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | ES_MULTILINE | ES_AUTOVSCROLL, 100, 460, 430, 220, hWnd, NULL, NULL, NULL);
}
void PE1()
{
	int n, i, j, k, current_time, counter, available, sum_TAT = 0, sum_WT = 0;
	strcpy(buffer,"");
	n=_n_;
	//PSL
    SetWindowText(PSL,buffer);
	GetValues();
	for (i = 0; i < n; i++)
	{
		sprintf(temporary,"%d\t%d\t%d\r\n", p[i].AT, p[i].BT, p[i].P);
		strcat(buffer,temporary);
		p[i].BT_remaining = p[i].BT;
		p[i].init_scheduling = -1;
		p[i].process_no=i;
	}
	current_time = p[0].AT;
	counter = 0;//Count the number of processes that have finished execution
	sprintf(temporary,"\r\nPre-emptive priority scheduling without Aging:\r\n\r\nGantt chart:\r\n");
    strcat(buffer,temporary);
    while (counter < n)
	{
		available = 0;
		for (i = counter; i < n; i++)
		{
			if (p[i].AT <= current_time)
            available++;
		}
		for (i = counter; i <= counter + available; i++)
		{
			for (j = counter; j < (counter + available - 1); j++)
			{
				if (p[j + 1].P > p[j].P)
				{
					temp = p[j];
					p[j] = p[j + 1];
					p[j + 1] = temp;
				}
			}
		}
		if (p[counter].init_scheduling == -1)
		{
			p[counter].init_scheduling = current_time;
			p[counter].RT = current_time - p[counter].AT;
		}
		p[counter].BT_remaining -= 1;
		if(p[counter].BT_remaining!=-1)
		{
		    sprintf(temporary,"\r\n%d-%d: P%d", current_time, current_time + 1, p[counter].process_no);
		    strcat(buffer,temporary);
            current_time += 1;
        }
		else
        {
            sprintf(temporary,"\r\n%d-%d: P%d", current_time, current_time, p[counter].process_no);
            strcat(buffer,temporary);
        }
        if (p[counter].BT_remaining <=0)
        {
            p[counter].CT = current_time;
            p[counter].TAT = p[counter].CT - p[counter].AT;
            p[counter].WT = p[counter].TAT - p[counter].BT;
            sum_TAT += p[counter].TAT;
            sum_WT += p[counter].WT;
            counter++;
        }
	}
	sprintf(temporary,"\r\n\r\n\tAverage Turn Around Time (TAT) is %.2f", (float)sum_TAT / n);
	strcat(buffer,temporary);
	sprintf(temporary,"\r\n\r\n\tAverage Waiting Time (WT) is %.2f", (float)sum_WT / n);
	strcat(buffer,temporary);
    SetWindowText(PSL,buffer);
}
void PE2()
{
    int n, i, j, k, current_time, counter, available, sum_TAT = 0, sum_WT = 0;
	n=_n_;
	//PSL
    GetWindowText(PSL,buffer,1000);
    strcat(buffer,"\r\n\r\n");
	GetValues();
	for (i = 0; i < n; i++)
	{
		p[i].BT_remaining = p[i].BT;
		p[i].init_scheduling = -1;
		p[i].process_no=i;
	}
	counter = 0;//Count the number of processes that have finished execution
    sprintf(temporary,"\r\nPre-emptive priority scheduling with Aging:\r\n\r\nGantt chart:\r\n");
    strcat(buffer,temporary);
    for(i=0;i<n;i++)
    {
        p[i].BT_remaining=p[i].BT;
        p[i].init_scheduling=-1;
    }
    current_time = p[0].AT;
    counter=0;
    sum_TAT=0;
    sum_WT=0;
    while(counter<n)
    {
        available=0;
        for(i=counter;i<n;i++)
        {
            if(p[i].AT<=current_time)
            {
                available++;
                p[i].P+=aging_value;
            }
        }
        for(i=counter;i<=counter+available;i++)
        {
            for(j=counter;j<(counter+available-1);j++)
            {
                if(p[j+1].P>p[j].P)
                {
                    temp=p[j];
                    p[j]=p[j+1];
                    p[j+1]=temp;
                }
            }
        }
        if(p[counter].init_scheduling==-1)
        {
            p[counter].init_scheduling=current_time;
            p[counter].RT=current_time-p[counter].AT;
        }
        p[counter].BT_remaining-=1;
        if(p[counter].BT_remaining!=-1)
		{
            sprintf(temporary,"\r\n%d-%d: P%d", current_time, current_time + 1, p[counter].process_no);
            strcat(buffer,temporary);
            current_time += 1;
		}
		else
        {
            sprintf(temporary,"\r\n%d-%d: P%d", current_time, current_time, p[counter].process_no);
            strcat(buffer,temporary);
        }
        if(p[counter].BT_remaining<=0)
        {
            p[counter].CT=current_time;
            p[counter].BT_remaining=0;
            p[counter].TAT=p[counter].CT-p[counter].AT;
            p[counter].WT=p[counter].TAT-p[counter].BT;
            sum_TAT+=p[counter].TAT;
            sum_WT+=p[counter].WT;
            counter++;
        }
    }
    sprintf(temporary,"\r\n\r\n\tAverage Turn Around Time (TAT) is %.2f",(float)sum_TAT/n);
    strcat(buffer,temporary);
    sprintf(temporary,"\r\n\r\n\tAverage Waiting Time (WT) is %.2f",(float)sum_WT/n);
    strcat(buffer,temporary);
    SetWindowText(PSL,buffer);
}
void NPE1()
{
    int n,i,j,k,current_time,counter,available,sum_TAT=0,sum_WT=0;
    strcpy(buffer,"");
	n=_n_;
	//PSL
    SetWindowText(PSL,buffer);
	GetValues();
	for (i = 0; i < n; i++)
	{
		sprintf(temporary,"%d\t%d\t%d\r\n", p[i].AT, p[i].BT, p[i].P);
		strcat(buffer,temporary);
		p[i].init_scheduling = -1;
		p[i].process_no=i;
	}
    current_time = p[0].AT;
    counter=0;//Count the number of processes that have finished execution
    sprintf(temporary,"\r\nNon-Pre-emptive priority scheduling without Aging:\r\n\r\nGantt chart:\r\n");
    strcat(buffer,temporary);
    while(counter<n)
    {
        available=0;
        for(i=counter;i<n;i++)
        {
            if(p[i].AT<=current_time)
            available++;
        }
        for(i=counter;i<=(counter+available);i++)
        {
            for(j=counter;j<(counter+available-1);j++)
            {
                if(p[j+1].P>p[j].P)
                {
                    temp=p[j];
                    p[j]=p[j+1];
                    p[j+1]=temp;
                }
            }
        }
        if(p[counter].init_scheduling==-1)
        {
            p[counter].init_scheduling=current_time;
        }
        sprintf(temporary,"\r\n%d-%d: P%d",current_time,current_time+p[counter].BT,p[counter].process_no);
        strcat(buffer,temporary);
        p[counter].CT=current_time;
        p[counter].TAT=p[counter].CT-p[counter].AT;
        p[counter].WT=p[counter].TAT-p[counter].BT;
        sum_TAT+=p[counter].TAT;
        sum_WT+=p[counter].WT;
        current_time+=p[counter].BT;
        counter++;
    }
    sprintf(temporary,"\r\n\r\n\tAverage Turn Around Time (TAT) is %.2f",(float)sum_TAT/n);
    strcat(buffer,temporary);
    sprintf(temporary,"\r\n\r\n\tAverage Waiting Time (WT) is %.2f",(float)sum_WT/n);
    strcat(buffer,temporary);
    SetWindowText(PSL,buffer);
}
void NPE2()
{
    int n,i,j,k,current_time,counter,available,sum_TAT=0,sum_WT=0;
	n=_n_;
	//PSL
    GetWindowText(PSL,buffer,1000);
    strcat(buffer,"\r\n\r\n");
    GetValues();
	for (i = 0; i < n; i++)
	{
		p[i].BT_remaining = p[i].BT;
		p[i].init_scheduling = -1;
		p[i].process_no=i;
	}
	current_time = p[0].AT;
	counter = 0;//Count the number of processes that have finished execution
    sprintf(temporary,"\r\nNon-Pre-emptive priority scheduling with Aging:\r\n\r\nGantt chart:\r\n");
    strcat(buffer,temporary);
    for(i=0;i<n;i++)
    {
        p[i].init_scheduling=-1;
    }
    while(counter<n)
    {
        available=0;
        for(i=counter;i<n;i++)
        {
            if(p[i].AT<=current_time)
            {
                available++;
                p[i].P+=aging_value;
            }
        }
        for(i=counter;i<=(counter+available);i++)
        {
            for(j=counter;j<(counter+available-1);j++)
            {
                if(p[j+1].P>p[j].P)
                {
                    temp=p[j];
                    p[j]=p[j+1];
                    p[j+1]=temp;
                }
            }
        }
        if(p[counter].init_scheduling==-1)
        {
            p[counter].init_scheduling=current_time;
        }
        sprintf(temporary,"\r\n%d-%d: P%d",current_time,current_time+p[counter].BT,p[counter].process_no);
        strcat(buffer,temporary);
        p[counter].CT=current_time;
        p[counter].TAT=p[counter].CT-p[counter].AT;
        p[counter].WT=p[counter].TAT-p[counter].BT;
        sum_TAT+=p[counter].TAT;
        sum_WT+=p[counter].WT;
        current_time+=p[counter].BT;
        counter++;
    }
    sprintf(temporary,"\r\n\r\n\tAverage Turn Around Time (TAT) is %.2f",(float)sum_TAT/n);
    strcat(buffer,temporary);
    sprintf(temporary,"\r\n\r\n\tAverage Waiting Time (WT) is %.2f",(float)sum_WT/n);
    strcat(buffer,temporary);
    SetWindowText(PSL,buffer);
}
void GetValues()
{
    //p0
	GetWindowTextW(P0AT, buff, 5);
	p[0].AT = _wtoi(buff);
	GetWindowTextW(P0BT, buff, 5);
	p[0].BT = _wtoi(buff);
	GetWindowTextW(P0P, buff, 5);
	p[0].P = _wtoi(buff);
	//p1
	GetWindowTextW(P1AT, buff, 5);
	p[1].AT = _wtoi(buff);
	GetWindowTextW(P1BT, buff, 5);
	p[1].BT = _wtoi(buff);
	GetWindowTextW(P1P, buff, 5);
	p[1].P = _wtoi(buff);
	//p2
	GetWindowTextW(P2AT, buff, 5);
	p[2].AT = _wtoi(buff);
	GetWindowTextW(P2BT, buff, 5);
	p[2].BT = _wtoi(buff);
	GetWindowTextW(P2P, buff, 5);
	p[2].P = _wtoi(buff);
	//p3
	GetWindowTextW(P3AT, buff, 5);
	p[3].AT = _wtoi(buff);
	GetWindowTextW(P3BT, buff, 5);
	p[3].BT = _wtoi(buff);
	GetWindowTextW(P3P, buff, 5);
	p[3].P = _wtoi(buff);
	//p4
	GetWindowTextW(P4AT, buff, 5);
	p[4].AT = _wtoi(buff);
	GetWindowTextW(P4BT, buff, 5);
	p[4].BT = _wtoi(buff);
	GetWindowTextW(P4P, buff, 5);
	p[4].P = _wtoi(buff);
	//p5
	GetWindowTextW(P5AT, buff, 5);
	p[5].AT = _wtoi(buff);
	GetWindowTextW(P5BT, buff, 5);
	p[5].BT = _wtoi(buff);
	GetWindowTextW(P5P, buff, 5);
	p[5].P = _wtoi(buff);
	//p6
	GetWindowTextW(P6AT, buff, 5);
	p[6].AT = _wtoi(buff);
	GetWindowTextW(P6BT, buff, 5);
	p[6].BT = _wtoi(buff);
	GetWindowTextW(P6P, buff, 5);
	p[6].P = _wtoi(buff);
}
void AutoFill()
{
    //p0
    p[0].AT = 0;
    _itow(0,buff,10);
	SetWindowTextW(P0AT,buff);
	p[0].BT = 4;
	_itow(4,buff,10);
	SetWindowTextW(P0BT,buff);
	p[0].P = 2;
	_itow(2,buff,10);
	SetWindowTextW(P0P, buff);
	//p1
	p[1].AT = 1;
    _itow(1,buff,10);
	SetWindowTextW(P1AT,buff);
	p[1].BT = 2;
	_itow(2,buff,10);
	SetWindowTextW(P1BT,buff);
	p[1].P = 4;
	_itow(4,buff,10);
	SetWindowTextW(P1P, buff);
	//p2
	p[2].AT = 2;
    _itow(2,buff,10);
	SetWindowTextW(P2AT,buff);
	p[2].BT = 3;
	_itow(3,buff,10);
	SetWindowTextW(P2BT,buff);
	p[2].P = 6;
	_itow(6,buff,10);
	SetWindowTextW(P2P, buff);
	//p3
	p[3].AT = 3;
    _itow(3,buff,10);
	SetWindowTextW(P3AT,buff);
	p[3].BT = 5;
	_itow(5,buff,10);
	SetWindowTextW(P3BT,buff);
	p[3].P = 10;
	_itow(10,buff,10);
	SetWindowTextW(P3P, buff);
	//p4
    p[4].AT = 4;
    _itow(4,buff,10);
	SetWindowTextW(P4AT,buff);
	p[4].BT = 1;
	_itow(1,buff,10);
	SetWindowTextW(P4BT,buff);
	p[4].P = 8;
	_itow(8,buff,10);
	SetWindowTextW(P4P, buff);
	//p5
    p[5].AT = 5;
    _itow(5,buff,10);
	SetWindowTextW(P5AT,buff);
	p[5].BT = 4;
	_itow(4,buff,10);
	SetWindowTextW(P5BT,buff);
	p[5].P = 12;
	_itow(12,buff,10);
	SetWindowTextW(P5P, buff);
	//p6
    p[6].AT = 6;
    _itow(6,buff,10);
	SetWindowTextW(P6AT,buff);
	p[6].BT = 6;
	_itow(6,buff,10);
	SetWindowTextW(P6BT,buff);
	p[6].P = 9;
	_itow(9,buff,10);
	SetWindowTextW(P6P, buff);
}
void ClearAll()
{
	//p0
	SetWindowText(P0AT,"");
	SetWindowText(P0BT,"");
	SetWindowText(P0P, "");
	//p1
	SetWindowText(P1AT,"");
	SetWindowText(P1BT,"");
	SetWindowText(P1P, "");
	//p2
	SetWindowText(P2AT,"");
	SetWindowText(P2BT,"");
	SetWindowText(P2P, "");
	//p3
	SetWindowText(P3AT,"");
	SetWindowText(P3BT,"");
	SetWindowText(P3P, "");
	//p4
	SetWindowText(P4AT,"");
	SetWindowText(P4BT,"");
	SetWindowText(P4P, "");
	//p5
	SetWindowText(P5AT,"");
	SetWindowText(P5BT,"");
	SetWindowText(P5P, "");
	//p6
	SetWindowText(P6AT,"");
	SetWindowText(P6BT,"");
	SetWindowText(P6P, "");
}
void AddMenus(HWND hWnd)
{
    hMenu=CreateMenu();
    AppendMenu(hMenu,MF_STRING,Clear_All,"Clear all");
    AppendMenu(hMenu,MF_STRING,Auto_Fill,"Auto fill");
    SetMenu(hWnd,hMenu);
}
