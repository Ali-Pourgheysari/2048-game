#include "2048.h"
int main()
{
    FILE *fp, *fp2;
    gamerec scoreboard;
    int rows, cols, i1, i2;
    fp = fopen("data.txt","rt");// We have 2 files in this game. one for scoreboard and one for game chart.
    if(!fp){
        cout << "               -------------WELCOME TO THE 2048 GAME-------------" << "\n\n\t\t    ";
        fp2 = fopen("data2.txt", "rt");// This file saves the details of scoreboard.
        if(!fp2)
        {
            fp2 = fopen("data2.txt", "wt");// If we did't have a former file, it will write a new one.
            cout << "Be the first player to play this game!";
        }
        else
        {
            cout  << "   Score \t\t\t Name" << "\n\n";
            fread(&scoreboard, sizeof(scoreboard), 1, fp2); // If we had a file, it will read it.
            while(!feof(fp2))// Like what the Mr.Mahvash said, we have to read a file twice otherwise it won't recognize the end of file.
            {
                cout << "\n\t\t\t" << scoreboard.scoresave;
                cout << "\t\t\t " <<scoreboard.name;
                fread(&scoreboard, sizeof(scoreboard), 1, fp2);
            }
        }
        cout << "\n\n" << "Please enter your name: ";
        cin >> scoreboard.name;
        fp2 = fopen("data2.txt","at");// It will save the name of new player for scoreboard.
        fwrite(scoreboard.name, sizeof(scoreboard.name), 1, fp2);
        fclose(fp2);
        cout << "\n\n" << "\nEnter rows and columns of the chart(rows and columns must be between 2 and 12): ";
        cin >> rows >> cols;
        newgame(rows,cols);
        printgame(rows,cols);

    }
    else
    {
        fread(&rows,sizeof(int),1,fp); // If we had a former file for chart it will read it.
        fread(&cols,sizeof(int),1,fp);
        fread(&score,sizeof(int),1,fp);
        fread(&score2,sizeof(int),1,fp);
        fread(console,sizeof(int),121,fp);
        fread(temp,sizeof(int),121,fp);
        fread(temp2,sizeof(int),121,fp);

        printgame(rows,cols);
    }

    fclose(fp);

    srand(time(NULL));// For random numbers we need this.
    system("cls");//for not printing chart every time we press a bottom we need this.


    bool flag, jlag , save;
    char command;

        while(true)
        {
            system("cls");
            cout << "Use arrows to control the game. (q: quit, n: new game, u: undo) \n\n";
            cout << "your score: " << score;

            fp = fopen("data.txt","wt");
            fwrite(&rows,sizeof(int),1,fp);
            fwrite(&cols,sizeof(int),1,fp);
            fwrite(&score,sizeof(int),1,fp);
            fwrite(&score2,sizeof(int),1,fp);
            fwrite(console,sizeof(int),121,fp);
            fwrite(temp,sizeof(int),121,fp);
            fwrite(temp2,sizeof(int),121,fp);
            fclose(fp);

            printgame(rows,cols);

            if(win(rows, cols) == 1)
            {
                cout << "\n\n\t\t\t\tYOU WON! GOOD JOB";
                break;
            }

            command = getch();
            flag = false, jlag = false, save = false;
            switch(command){ // The arrows ASCII code are the same as P, H, M, and k. also You are able to play with w,d,s,and a characters.
                case 'S':
                case 's':
                case 80 :movedown(rows, cols, jlag);
                         break;
                case 'W':
                case 'w':
                case 72 :moveup(rows, cols, jlag);
                         break;
                case 'D':
                case 'd':
                case 77 :moveright(rows, cols, jlag);
                         break;
                case 'A':
                case 'a':
                case 75 :moveleft(rows, cols, jlag);
                         break;
                case 'N':
                case 'n':newgame(rows, cols);
                         break;
                case 'Q':
                case 'q':flag = true;
                         break;
                case 'U':
                case 'u':for( int i = 0; i < rows; i++)
                            for( int j = 0; j < cols; j++)
                                console[i][j] = temp[i][j];
                                score = score2;
                         break;
            }
            if(flag){ // This is for quitting the game. you can whether save it or not.
                cout << "\n\n\t    Are you sure you want to quit the game? (y:yes, n:no)";
                char ask = getch();
                if(ask == 'y' || ask == 'Y'){
                    cout << "\n\n\t\t Do you want to save your game? (y:yes, n:no)";
                    char ask2 = getch();
                    if(ask2 == 'y' || ask2 == 'Y')
                        save = true;
                    cout << "\n\n\t\t\t\tYou quit the game \n";
                    break;
                }
            }

            if(gameover(rows, cols) == 1)
            {
                cout << "\n\n\t\t\t\t  GAME OVER!\n";
                break;
            }

            if(jlag) // This is for saving the chart for undo.
                for( int i = 0; i < rows; i++)
                    for( int j = 0; j < cols; j++){
                        temp[i][j] = temp2[i][j];
                    }

            if(jlag){ // This is for a random number.
                while(1){
                    i1=rand()% rows;
                    i2=rand()% cols;
                    if(console[i1][i2] == 0) break;
                }
            console[i1][i2] = 2;
            }
        }

    if(!save){ // It will save second file for scoreboard and remove the first file for the chart.
        scoreboard.scoresave = score;
        fp2 = fopen("data2.txt","at");
        fwrite(&scoreboard.scoresave, sizeof(scoreboard.scoresave), 1, fp2);
        fclose(fp2);
        int result = remove("data.txt");
    }
    return 0;
}

void movedown(int rows, int cols, bool &jlag) //If you press down arrow this function will work.
{
    int i, j, k;

    for( i = 0; i < rows; i++)
            for( j = 0; j < cols; j++)
                temp2[i][j] = console[i][j]; // for undo we save the main array in the tow temporary arrays.
    score2 = score;

    for( j = 0; j < cols; j++)
        for(k = 0; k < rows; k++)
            for( i = rows - 2; i>= 0; i--)
                if(console[i+1][j] == 0 && console[i][j]!= 0){
                    console[i+1][j] = console[i][j];
                    console[i][j] = 0;
                    jlag = true;
                }
    for( j = 0; j < cols; j++)
        for( i = rows - 2; i >= 0; i--)
            if(console[i][j] == console[i+1][j] && console[i][j] != 0){
                score += console[i+1][j] += console[i][j];
                console[i][j] = 0;
                i--;
                jlag = true;
            }
    for( j = 0; j < cols; j++)
        for(k = 0; k < rows; k++)
            for( i = rows - 2; i>= 0; i--)
                if(console[i+1][j] == 0 && console[i][j]!= 0){
                    console[i+1][j] = console[i][j];
                    console[i][j] = 0;
                    jlag = true;
                }

}

void moveup(int rows, int cols, bool &jlag)//If you press up arrow this function will work.
{
    int i, j, k;

    for( i = 0; i < rows; i++)
            for( j = 0; j < cols; j++)
                temp2[i][j] = console[i][j];// for undo we save the main array in the tow temporary arrays.
    score2 = score;

    for( j = 0; j < cols; j++)
        for(k = 0; k < rows; k++)
            for( i = 1; i < rows ; i++)
                if(console[i-1][j] == 0 && console[i][j]!= 0){
                    console[i-1][j] = console[i][j];
                    console[i][j] = 0;
                    jlag = true;
                }
    for( j = 0; j < cols; j++)
        for( i = 1; i < rows ; i++)
            if(console[i][j] == console[i-1][j] && console[i][j] != 0){
                score += console[i-1][j] += console[i][j];
                console[i][j] = 0;
                i++;
                jlag = true;
            }
    for( j = 0; j < cols; j++)
        for(k = 0; k < rows; k++)
            for( i = 1; i < rows ; i++)
                if(console[i-1][j] == 0 && console[i][j]!= 0){
                    console[i-1][j] = console[i][j];
                    console[i][j] = 0;
                    jlag = true;
                }
}

void moveright(int rows, int cols, bool &jlag)//If you press right arrow this function will work.
{
    int i, j, k;

    for( i = 0; i < rows; i++)
            for( j = 0; j < cols; j++)
                temp2[i][j] = console[i][j];// for undo we save the main array in the tow temporary arrays.
    score2 = score;

    for( i = 0; i < rows; i++)
        for(k = 0; k < cols; k++)
            for( j = cols - 2; j>= 0; j--)
                if(console[i][j+1] == 0 && console[i][j]!= 0){
                    console[i][j+1] = console[i][j];
                    console[i][j] = 0;
                    jlag = true;
                }
    for( i = 0; i < rows; i++)
        for( j = cols - 2; j >= 0; j--)
            if(console[i][j] == console[i][j+1] && console[i][j] != 0){
                score += console[i][j+1] += console[i][j];
                console[i][j] = 0;
                j--;
                jlag = true;
            }
    for( i = 0; i < rows; i++)
        for(k = 0; k < cols; k++)
            for( j = cols - 2; j>= 0; j--)
                if(console[i][j+1] == 0 && console[i][j]!= 0){
                    console[i][j+1] = console[i][j];
                    console[i][j] = 0;
                    jlag = true;
                }

}

void moveleft(int rows, int cols, bool &jlag)//If you press left arrow this function will work.
{
    int i, j, k;

    for( i = 0; i < rows; i++)
            for( j = 0; j < cols; j++)
                temp2[i][j] = console[i][j];// for undo we save the main array in the tow temporary arrays.
    score2 = score;

    for( i = 0; i < rows; i++)
        for(k = 0; k < cols; k++)
            for( j = 1; j < cols; j++)
                if(console[i][j-1] == 0 && console[i][j]!= 0){
                    console[i][j-1] = console[i][j];
                    console[i][j] = 0;
                    jlag = true;
                }
    for( i = 0; i < rows; i++)
        for( j = 1; j < cols ; j++)
            if(console[i][j] == console[i][j-1] && console[i][j] != 0){
                score += console[i][j-1] += console[i][j];
                console[i][j] = 0;
                j++;
                jlag = true;
            }
    for( i = 0; i < rows; i++)
        for(k = 0; k < cols; k++)
            for( j = 1; j < cols; j++)
                if(console[i][j-1] == 0 && console[i][j]!= 0){
                    console[i][j-1] = console[i][j];
                    console[i][j] = 0;
                    jlag = true;
                }
}


void newgame(int rows, int cols)
{
    for(int i = 0; i < 11; i++)
        for(int j = 0; j < 11; j++)
            console[i][j] = 0;
    score = 0;

    int i1, i2, i3, i4;

        i1=rand()% rows;
        i2=rand()% cols;
        while(1)
        {
            i3=rand()% rows;
            i4=rand()% cols;
            if(i3!=i1 && i4!=i2) break;
        }
    console[i1][i2]=2;
    console[i3][i4]=2;
    temp[i1][i2]=2;
    temp[i3][i4]=2;

}

void printgame(int rows,int cols)// This is for printing the game on the console.
{
    int sizeo;
    cout<<"\n\n\n";
	int i,j;
	for(i=0;i<rows;i++)
	{
	    cout<<"\t";
	    for(int k=0;k<cols;k++)
            cout << "------";
        cout<<"-\n\t";
		for(j=0;j<cols;j++)// This loop manage the chart to be in the best form by counting the digits.
		{
			if(console[i][j]==0) cout<<"|     ";

			else{
                sizeo = (int) log10(console[i][j]) + 1;
                switch(sizeo){
                    case 1: cout<<"|  " <<console[i][j]<<"  ";
                            break;
                    case 2: cout<<"|  "<<console[i][j]<<" ";
                            break;
                    case 3: cout<<"| "<<console[i][j]<<" ";
                            break;
                    default: cout<<"| "<<console[i][j]<<"";

                }
			}
		}
		cout<<"|"<<endl;
	}
	cout<<"\t";
	    for(int k=0;k<cols;k++)
            cout << "------";
        cout<<"-\n";
}

int gameover(int rows, int cols)
{
    int i, j;
    if(cols == 2)
    {
    for(i = 0; i < rows; i++)
        for(j = 1; j < 2; j++)
            if(console[i][j-1] == console[i][j])
                return 0;
    }
    if(rows == 2)
    {
    for(j = 0; j < cols; j++)
        for(i = 1; i < 2; i++)
            if(console[i-1][j] == console[i][j])
                return 0;

    }
    for(i = 0; i < rows; i++)
        for(j = 1; j < cols-1; j++)
            if(console[i][j-1] == console[i][j] || console[i][j] == console[i][j+1])
                return 0;

    for(j = 0; j < cols; j++)
        for(i = 1; i < rows - 1; i++)
            if(console[i-1][j] == console[i][j] || console[i][j] == console[i+1][j])
                return 0;

    for(j = 0; j < cols; j++)
        for(i = 0; i < rows ; i++)
            if(console[i][j] == 0)
                return 0;


    return 1;
}

int win(int rows, int cols)
{
    int i, j;
    for(i = 0; i < rows; i++)
        for(j = 0; j < cols; j++)
            if(console[i][j] == 2048)
                return 1;
    return 0;
}
