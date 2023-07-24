import Phaser from 'phaser';
import player1 from './assets/bar_red_00.png';
import player2 from './assets/bar_red_00.png';
import bl from './assets/ball_red_00.png';
import background from './assets/terrain_pong_01.png';

//--------------------------------------------- class ------------------------------------------------//

class Vec2 {
	constructor(x, y) {
		this.x = x;
		this.y = y;
	}
}

class Rect {
	constructor(x, y, width, height) {
		this.x = x;
		this.y = y;
		this.width = width;
		this.height = height;
	}
}

class HitPoint {
	constructor(rect1, rect2, pos, side) {
		this.rect1 = rect1;
		this.rect2 = rect2;
		this.pos = pos;
		this.side = side;
	}
}

class Player {
	constructor(hit, imgLink, obj, hitZone) {
		this.hitPoint = hit;
		this.imgLink = imgLink;
		this.obj = obj;
		this.hitZone = hitZone;
	}
}

//--------------------------------------------- Vars -------------------------------------------------//

let p1 = new Player([0, 0], player1, 0, [0, 0, 0, 0, 0]);
let p2 = new Player([0, 0], player2, 0, [0, 0, 0, 0, 0]);

let ball = new Player([0, 0], player2, 0, [0, 0, 0, 0, 0]);
let ballAngleModifier = 0;

let ctUpP1 = 0;
let ctDownP1 = 0;
let ctUpP2 = 0;
let ctDownP2 = 0;

let ctBall = -1;
let ctBallBound = -1;

//----------------------------------------- catch key events ------------------------------------------//
// Add event listener on keydown

document.addEventListener('keydown', (event) => {
	MovePlayerDown(event);
}, true);
document.addEventListener('keyup', (event) => {
	MovePlayerUp(event);
}, true);

//----------------------------------------------- class -----------------------------------------------//

class MyGame extends Phaser.Scene
{
	constructor ()
	{
		super();
	}

	preload ()
	{
		this.load.image('p1', p1.imgLink);
		this.load.image('p2', p1.imgLink);
		this.load.image('ball', bl);
		this.load.image('background', background);
	}

	create ()
	{
		const bg = this.add.image(600, 400, 'background');

		p1.obj = this.add.image(1170, 400, 'p1');

		p2.obj = this.add.image(30, 400, 'p2');

		ball.obj = this.add.image(600, 400, 'ball');
		// ball.setCollideWorldBounds(true);	// rebound in screen side

		// this.tweens.add({
		// 	targets: p1,
		// 	y: 0,
		// 	duration: 2000,
		// 	ease: "",
		// 	yoyo: true,
		// 	loop: 0
		// });
	}

	update()
	{
		ControlP1();
		ControlP2();

		BallControl();
		
		CheckCollision();
		SavePositions();
	}
}

const config = {
	type: Phaser.AUTO,
	parent: 'phaser-example',
	width: 1200,
	height: 800,
	// physics: {
	// 	default: 'arcade',
	// 	arcade: {
	// 	  gravity: { }, // Ajoutez les propriétés de physique nécessaires
	// 	  // Autres options de configuration de la physique
	// 	}
	// },
	scene: MyGame
};

const game = new Phaser.Game(config);

//---------------------------------------------- Execution ----------------------------------------------//

function MovePlayerDown(event) {
	const keyPressed = event.key;
	// console.log("You hit Down: " + keyPressed);

	// P1 up and down ct
	if (keyPressed === 'o') {

		ctUpP1 = 1;
	}
	if (keyPressed === 'l') {
		ctDownP1 = 1;
	}


		// P2 up and down ct
	if (keyPressed === 'w') {
		ctUpP2 = 1;
	}
	if (keyPressed === 's') {
		ctDownP2 = 1;
	}

	if (keyPressed === 'z') {
		ctBall = ctBall * -1;
	}
}

function MovePlayerUp(event) {
	const keyPressed = event.key;
	// console.log("You hit Up: " + keyPressed);

	// P1 up and down
	if (keyPressed === 'o') {
		ctUpP1 = 0;
	}
	if (keyPressed === 'l') {
		ctDownP1 = 0;
	}

	// P2 up and down
	if (keyPressed === 'w') {
		ctUpP2 = 0;
	}
	if (keyPressed === 's') {
		ctDownP2 = 0;
	}
}

function BallControl() {
	if (ctBall == 1) {
		ball.obj.x -= 6;
		ball.obj.y += ballAngleModifier;
	}
	else if (ctBall == -1) {
		ball.obj.x += 6;
		ball.obj.y += ballAngleModifier;
	}

	if (ball.hitZone.y1 <= 5)
	{
		ballAngleModifier *= -1;
		ball.obj.y = 24;
	}
	else if (ball.hitZone.y2 >= 795)
	{
		ballAngleModifier *= -1;
		ball.obj.y = 776;
	}
	// console.log("rebound 1: " + ball.hitZone.y1);
	// console.log("rebound 2: " + ball.hitZone.y2);
	// console.log("ballAngleModifier: " + ballAngleModifier);
}

function ControlP1() {
	// p1 up down
	if (ctUpP1 == 1 && p1.obj.y > 84) {
		p1.obj.y -= 5;
	}
	if (ctDownP1 == 1 && p1.obj.y < 717) {
		p1.obj.y += 5;
	}
}

function ControlP2() {
	// p2 up down
	if (ctUpP2 == 1 && p2.obj.y > 84) {
		p2.obj.y -= 5;
	}
	if (ctDownP2 == 1 && p2.obj.y < 717) {
		p2.obj.y += 5;
	}
}

function SavePositions() {
	p1.hitZone.x1 = p1.obj.x - (p1.obj.width / 2);
	p1.hitZone.x2 = p1.obj.x + (p1.obj.width / 2);
	p1.hitZone.y1 = p1.obj.y - (p1.obj.height / 2);
	p1.hitZone.y2 = p1.obj.y + (p1.obj.height / 2);
	p1.hitZone.moyY = p1.hitZone.y1 + (p1.obj.height / 2);

	p2.hitZone.x1 = p2.obj.x - (p2.obj.width / 2);
	p2.hitZone.x2 = p2.obj.x + (p2.obj.width / 2);
	p2.hitZone.y1 = p2.obj.y - (p2.obj.height / 2);
	p2.hitZone.y2 = p2.obj.y + (p2.obj.height / 2);
	p2.hitZone.moyY = p2.hitZone.y1 + (p2.obj.height / 2);

	ball.hitZone.x1 = ball.obj.x - (ball.obj.width / 2);
	ball.hitZone.x2 = ball.obj.x + (ball.obj.width / 2);
	ball.hitZone.y1 = ball.obj.y - (ball.obj.height / 2);
	ball.hitZone.y2 = ball.obj.y + (ball.obj.height / 2);
	ball.hitZone.moyY = ball.hitZone.y1 + (ball.obj.height / 2);
}

function CheckCollision() {
	

	if (Phaser.Geom.Intersects.RectangleToRectangle(ball.obj.getBounds(), p1.obj.getBounds())) {
		// Collision detected player1 and ball

		// console.log("img.x1 : " + p1.hitZone.x1);
		// console.log("img.x2 : " + p1.hitZone.x2);
		// console.log("img.y1 : " + p1.hitZone.y1);
		// console.log("img.y2 : " + p1.hitZone.y2);
		// console.log("p1.moy   : " + p1.hitZone.moyY);
		// console.log("ball.moy : " + ball.hitZone.moyY);
		console.log("ballAngleModifier : " + ballAngleModifier);

		// console.log('Collision player1 and ball');
		if (ctBall == -1)
		{
			if (ball.hitZone.moyY > p1.hitZone.moyY)
			{
				ballAngleModifier += 0.5;
			}
			else if (ball.hitZone.moyY < p1.hitZone.moyY)
			{
				ballAngleModifier -= 0.5;
			}
			else
			{
				ballAngleModifier = 0;
			}

			if (ctUpP1 == 1)
			{
				// TODO: move in y
			}
			ctBall = ctBall * -1;
		}
	}
	else if (Phaser.Geom.Intersects.RectangleToRectangle(p2.obj.getBounds(), ball.obj.getBounds())) {
		// Collision detected player2 and ball
		console.log('Collision player2 and ball');

		if (ctBall == 1)
		{
			if (ball.hitZone.moyY > p2.hitZone.moyY)
			{
				ballAngleModifier += 0.3;
			}
			else if (ball.hitZone.moyY < p2.hitZone.moyY)
			{
				ballAngleModifier -= 0.3;
			}
			else
			{
				ballAngleModifier = 0;
			}

			if (ctUpP1 == 1)
			{
				// TODO: move in y
			}
			ctBall = ctBall * -1;
		}
	}

	// if sombody put a goal
	if (ball.obj.x > 1300)
	{
		// console.log('Player2 Win this round');
		ctBall = ctBall * -1;
		ball.obj.x = 600;
		ball.obj.y = 400;
		ballAngleModifier = 0;
	}
	else if (ball.obj.x < -100)
	{
		// console.log('Player1 Win this round');
		ctBall = ctBall * -1;
		lAngleModifier = 0;
	}
}