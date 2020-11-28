#include "game1grid.h"
Game1Grid::Game1Grid()
{
    srand(time(0));
    chance1 = new QLabel();
    chance1->setPixmap(QPixmap(":/thumbnails/heart.png").scaled(40,40));
    chance1->setFixedSize(40,40);
    chance1->setStyleSheet("QLabel {font-size:50px;color:white;background-color: rgba(255, 255, 255, 0);}");
    chance1->move(950,10);
    this->addWidget(chance1);

    chance2 = new QLabel();
    chance2->setPixmap(QPixmap(":/thumbnails/heart.png").scaled(40,40));
    chance2->setFixedSize(40,40);
    chance2->setStyleSheet("QLabel {font-size:50px;color:white;background-color: rgba(255, 255, 255, 0);}");
    chance2->move(900,10);
    this->addWidget(chance2);

    chance3 = new QLabel();
    chance3->setPixmap(QPixmap(":/thumbnails/heart.png").scaled(40,40));
    chance3->setFixedSize(40,40);
    chance3->setStyleSheet("QLabel {font-size:50px;color:white;background-color: rgba(255, 255, 255, 0);}");
    chance3->move(850,10);
    this->addWidget(chance3);

    save_score = false;
    paused_game = false;
    game_ended = false;
    pause_button = new ClickableLabel();
    pause_button->setPixmap(QPixmap(":/thumbnails/pause.png").scaled(50,50));
    pause_button->setFixedSize(50,50);
    pause_button->setStyleSheet("QLabel {font-size:50px;color:white;background-color: rgba(255, 255, 255, 0);}");
    pause_button->move(50,50);
    this->addWidget(pause_button);
    QObject::connect(pause_button,SIGNAL(clicked()),this,SLOT(ClickPause()));

    this->current_count=0;
    this->rolling_speed =1.0;
    setBackgroundBrush(QBrush(QColor::fromRgb(128,0,0),Qt::SolidPattern));
    this->setSceneRect(QRectF(0,0,1010,485));

    timer_info = new QLabel("00:00");
    timer = new QTimer();
    elapsed_time = 0;
    timer->start(1000);
    timer_info->move(865,50);
    timer_info->setFixedSize(150,40);
    timer_info->setStyleSheet("QLabel {font-size:40px;color:white;background-color: rgba(255, 255, 255, 0);}");
    this->addWidget(timer_info);
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(UpdateTime()));

    current_score = 0;
    score_info = new QLabel("0");
    score_info->move(500,50);
    score_info->setFixedSize(150,40);
    score_info->setStyleSheet("QLabel {font-size:50px;color:white;background-color: rgba(255, 255, 255, 0);}");

    this->addWidget(score_info);

    smashed_virus = new VirusObject();
    current_virus = 0;

    virus_loc = LoadGrid();

    spawn_timer = new QTimer();
    QObject::connect(spawn_timer,SIGNAL(timeout()),this,SLOT(SpawnVirus()));
    spawn_timer->start(2500.00/rolling_speed);

    game_over_timer = new QTimer();
    QObject::connect(game_over_timer,SIGNAL(timeout()),this,SLOT(GameOver()));
    game_over_timer->start(10);

    new_virus = NULL;
}

void Game1Grid::ShootVirus(){
    if (paused_game)
        return;
    VirusObject * source = qobject_cast<VirusObject*>(sender());
    if (source->isVisible()){
        //source->smash_sound->play();
        current_score += source->getScore();
        current_count += 1;
        if (current_count==5){
            this->rolling_speed *=1.25;
            current_count = 0;
            spawn_timer->start(double(2500.00/rolling_speed)+100);

        }
        score_info->setText(QStringLiteral("%1").arg(current_score));
        smashed_virus->move(source->x(),source->y());
        this->addWidget(smashed_virus);
        source->hide();
    }

}

vector<vector<int>> Game1Grid::LoadGrid(){
    QFile inputFile(":/game1_grid.txt");
    vector<vector<int>>next_virus;
    int theoretical_score = 0;
    if (inputFile.size()!=0){
        inputFile.open(QIODevice::ReadOnly);//configure to read
        QTextStream stream(&inputFile);
        QString line = stream.readLine();
        this->winning_score  = line.toInt();
        line = stream.readLine();
        while (!line.isNull() && theoretical_score!=winning_score) { //extract grid info from txt file
            QStringList tempLine = line.split(QRegExp(" |\t"));
            int increment =0;
            if (tempLine[0].toInt()==1)
                increment=3;
            else if (tempLine[0].toInt()==2)
                increment=5;
            else if (tempLine[0].toInt()==3)
                increment=7;
            theoretical_score+=increment;

            line = stream.readLine();
            vector<int> auxVector;
            auxVector.push_back(tempLine[0].toInt());
            auxVector.push_back(tempLine[1].toInt());
            auxVector.push_back(tempLine[2].toInt());
            next_virus.push_back(auxVector);
        }
        inputFile.close();
    }
    if (theoretical_score!=winning_score){
        winning_score = 150;
        theoretical_score = 0;
        next_virus.clear();
        for (int i=0;i<30;i++){
            vector<int>single_virus;
            if (i<10)
                single_virus.push_back(1);
            else if (i<20)
                single_virus.push_back(2);
            else
                single_virus.push_back(3);
            single_virus.push_back(rand()%900);
            single_virus.push_back(rand()%300 + 100);
            next_virus.push_back(single_virus);
        }

        std::random_shuffle(next_virus.begin(), next_virus.end());

    }
    return next_virus;

}
void Game1Grid::UpdateTime(){
    elapsed_time+=1;
    int sec = int(elapsed_time % 60);
    QString seconds = "";
    QString minutes = "";

    if (int(elapsed_time%60)<10)
        seconds = QStringLiteral("0%2").arg(int(elapsed_time%60));
    else
        seconds = QStringLiteral("%2").arg(int(elapsed_time%60));

    if (int(elapsed_time/60)<10)
        minutes = QStringLiteral("0%1").arg(int(elapsed_time/60));
    else
        minutes = QStringLiteral("%1").arg(int(elapsed_time/60));

    timer_info->setText(minutes + ":" + seconds);
}
void Game1Grid::SpawnVirus(){
    if(VirusObject::missed_shots.size()==0) {
        new_virus = new VirusObject(static_cast<VirusObject::Color>(virus_loc[current_virus][0]-1),this->rolling_speed);
        new_virus->move(virus_loc[current_virus][1],virus_loc[current_virus][2]);
        this->addWidget(new_virus);
        current_virus +=1;
    }
    else {
        new_virus = new VirusObject(static_cast<VirusObject::Color>(VirusObject::missed_shots.back()),this->rolling_speed);
        new_virus->move(int(rand()%900),rand()%300+100);
        this->addWidget(new_virus);
        VirusObject::missed_shots.pop_back();
    }
    QObject::connect(new_virus,SIGNAL(clicked()),this,SLOT(ShootVirus()));
}

void Game1Grid::GameOver(){
    if (VirusObject::total_misses==1){
        chance3->clear();
    }
    else if (VirusObject::total_misses==2){
        chance2->clear();
    }
    if (VirusObject::total_misses>=3 || current_score==winning_score){
        timer->stop();
        spawn_timer->stop();
        game_over_timer->stop();
        paused_game = true;
        game_ended = true;
        save_score = true;
        pause_menu = new QWidget();
        this->pause_button->clear();
        pause_menu->setAttribute(Qt::WA_DeleteOnClose);
        QGridLayout *temp  =new QGridLayout();
        QLabel * prompt = new QLabel("Press any button");
        prompt->setStyleSheet("QLabel {color:black; font-size:32px}");
        temp->addWidget(prompt,0,1);
        pause_menu->setLayout(temp);
        pause_menu->setFixedSize(300,100);
        pause_menu->move(365,200);
        this->addWidget(pause_menu);
   }
}
void Game1Grid::keyPressEvent(QKeyEvent *event){

    if (game_ended==true){
        pause_menu->close();
        emit(gameOver());
    }
}
void Game1Grid::ClickPause() {
    paused_game = true;
    this->timer->stop();
    this->game_over_timer->stop();
    this->spawn_timer->stop();
    if (new_virus!=NULL){
        this->new_virus->expiry_timer->stop();
    }
    pause_menu = new QWidget();
    pause_menu->setAttribute(Qt::WA_DeleteOnClose);
    QGridLayout *temp  =new QGridLayout();
    QPushButton * cont = new QPushButton("Resume");
    QPushButton * quit_game = new QPushButton("Quit");
    QObject::connect(quit_game,SIGNAL(clicked()),this,SLOT(QuitGame()));
    QObject::connect(cont,SIGNAL(clicked()),this,SLOT(ClickContinue()));
    temp->addWidget(cont,0,0);
    temp->addWidget(quit_game,0,1);
    pause_menu->setLayout(temp);
    this->addWidget(pause_menu);
    pause_menu->setFixedSize(300,100);
    pause_menu->move(365,200);
}

void Game1Grid::ClickContinue(){
    paused_game = false;
    this->timer->start(1000);
    this->game_over_timer->start(10);
    this->spawn_timer->start(2500.00/rolling_speed);
    if (new_virus!=NULL && !this->new_virus->expiry_timer->isActive())
        this->new_virus->expiry_timer->start(2500.00/rolling_speed +100);

    pause_menu->close();
    //delete this->pause_menu;
}

void Game1Grid::QuitGame(){
    save_score = false;
    emit(gameOver());
}

