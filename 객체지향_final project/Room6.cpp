#include "Room6.h"
#include "Consola.h"
#include "BackGround.h"
#include "View.h"
#include "Controller.h"


void Room6::paintRoom() {
	addEntrance(NORTH); // 0번
	addEntrance(SOUTH); // 1번
	addEntrance(EAST); // 2번


	// 아래는 paint. 순서를 고려해야함
	paintBackGround();	// 배경 출력

	paintEntrance();	// 입구 출력

	paintCharacter();	// 캐릭터 출력(반복문 및 키 입력)
}

void Room6::paintPattern() {
	int pattern[20][20] = {
	  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},//1
	  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	  {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	  {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},//5
	  {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	  {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	  {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	  {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	  {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},//10
	  {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},//11
	  {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	  {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},//15
	  {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	  {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	  {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}//20
	};

	Box b(BackGround::x, BackGround::y, 2, 1);

	for (int i = 0; i < 20; ++i) {
		for (int j = 0; j < 20; ++j) {
			if (pattern[i][j] == 1) { // 일반 벽
				b.paintBox(RED);
			}
			b.plusX(2);
		}
		b.setX(BackGround::x);
		b.plusY(1);
	}
}

// 사용자가 특정 좌표에서 space 키를 눌렀을 때, 캐릭터가 장애물과 충돌했는지 확인하는 상호작용 확인 함수
bool Room6::isImpacted() {
	// 캐릭터 포인터 획득
	Character* character = model->getCharacter();

	// 캐릭터의 x/y 좌표
	int charX = character->getXPos();
	int charY = character->getYPos();


	// 입구와도 충돌했는지 확인한다.
	for (Box b : entranceVector) {
		if (b.getX() <= charX && charX <= b.getX() + b.getWidth() && b.getY() <= charY && charY <= b.getY() + b.getHeight())
			return true;
	}
	return false;
}

// 남쪽 문과 상호작용했을 때 실행될 함수
void Room6::eventSouthEntranceFunc() {
	textbackground(WHITE);
	textcolor(BLACK);
	View::xyPutStr(BackGround::textFieldX, BackGround::textFieldY, "방으로 이동하시겠습니까?");
	// Yes와 No 중에서 선택한 후, 결과값을 받아온다.
	bool selected = selectYesNo();
	// enter를 눌렀을 때, 선택한 문자가 Yes인 경우
	if (selected) {
		isInRoom = false;
		View::clearAllText();
		Model::changeRoomNum(5);
		// 5번 방의 이전 방 설정을 해줘야 함
		view->getRoomVector()->at(5)->setPrevRoom(6);
		view->getRoomVector()->at(5)->setIsInRoom(true);
		model->getCharacter()->setStartLocation('U');
	}
	isTextPainted = true;
}



// 현재 캐릭터가 위치한 장애물을 반환하는 함수
Box* Room6::getCurrentObstacle() {
	// 캐릭터 포인터 획득
	Character* character = model->getCharacter();

	// 캐릭터의 x/y 좌표
	int charX = character->getXPos();
	int charY = character->getYPos();

	for (Box b : entranceVector) {
		if (b.getX() <= charX && charX <= b.getX() + b.getWidth() && b.getY() <= charY && charY <= b.getY() + b.getHeight())
			return &b;
	}
	return nullptr;
}



// -------------- mainCharacter ----------------- //
void Room6::paintCharacter() {
	Character* character = model->getCharacter();

	int key;

	textcolor(BLACK); // 캐릭터 색상
	textbackground(WHITE);
	View::xyPutStr(character->getXPos(), character->getYPos(), "!");
	paintPattern();
	// 현재 캐릭터가 계속해서 해당 방에 존재할 것이면 반복문 계속.
	while (isInRoom) {
		paintInterface();
		key = Controller::getKey();
		// 인터페이스가 출력되는 부분에 텍스트가 출력되어있다면, 해당 부분을 지운다.
		if (isTextPainted) {
			textbackground(BLACK);
			View::clearAllText();
			isTextPainted = false;
		}

		switch (key) {
		case UPKEY:		character->moveUp(); break;
		case DOWNKEY:	character->moveDown(); break;
		case LEFTKEY:	character->moveLeft(); break;
		case RIGHTKEY:	character->moveRight(); break;
		case SPACEKEY:
			if (isImpacted()) {
				Model::moveCount += 2;
				// 캐릭터가 장애물과 부딪혔다면, 현재 부딪힌 장애물을 얻어온다.
				Box* currentObstacle = getCurrentObstacle();
				if (*currentObstacle == entranceVector.at(0))
					eventNorthEntranceFunc(7);
				else if (*currentObstacle == entranceVector.at(1))
					eventSouthEntranceFunc();
				else if (*currentObstacle == entranceVector.at(2))
					eventEastEntranceFunc(8);
			}
			break;
		}
		if (!isInRoom) continue;

		paintPattern();

		textbackground(WHITE);
		textcolor(BLACK);
		View::xyPutStr(character->getOldXPos(), character->getOldYPos(), " "); // 잔상 처리
		View::xyPutStr(character->getXPos(), character->getYPos(), "!");
	}

}
