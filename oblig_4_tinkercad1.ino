	void setup() {
	  pinMode(2, OUTPUT);
	  pinMode(4, OUTPUT);
	  pinMode(7, OUTPUT);
	  pinMode(8, INPUT);
	  pinMode(12, INPUT);
	  pinMode(13, INPUT);
	}

	const int LOCKED = 1;
	const int WAITCLICKONE = 2;
	const int WAITCLICKTWO = 3;
	const int CHECKING = 4;
	const int UNLOCKED = 5;
	int state = LOCKED;
	
	int start = 0;
	int code[] = {1, 1};
	int codeTry[2];

	int buttonOneUsed = 0;
	int buttonTwoUsed = 0;
	  

	void loop() {
	  int buttonOne = digitalRead(12);
	  int buttonTwo = digitalRead(8);
	  int sensor = digitalRead(13);
	  
	  if(buttonOne == LOW) buttonOneUsed = 0;
	  if(buttonTwo == LOW) buttonTwoUsed = 0;
	  
	  switch(state) {
	  
	    case LOCKED:
	      digitalWrite(7, HIGH);
	      if(sensor == HIGH) {
	        digitalWrite(7, LOW);
	        state = WAITCLICKONE;
	        start = millis();
	      }
	      break;
	    
	    case WAITCLICKONE:
	      digitalWrite(4, HIGH);
	      if(buttonOne == HIGH && !buttonOneUsed) {
	         buttonOneUsed = 1;
	         codeTry[0] = 1;
	         digitalWrite(4, LOW);
	         delay(200);
	         state = WAITCLICKTWO;
	      }
	      
	      if(buttonTwo == HIGH && !buttonTwoUsed) {
	         buttonTwoUsed = 1;
	         codeTry[0] = 2;
	         digitalWrite(4, LOW);
	         delay(200);
	         state = WAITCLICKTWO;
	      }
	    
	      if(millis() - start > 10000) {
	         digitalWrite(4, LOW);
	         state = LOCKED;
	      }
	      break;
	    
	    case WAITCLICKTWO:
	      digitalWrite(4, HIGH);
	      if(buttonOne == HIGH && !buttonOneUsed) {
	         buttonOneUsed = 1;
	         codeTry[1] = 1;
	         digitalWrite(4, LOW);
	         delay(200);
	         digitalWrite(4, HIGH);
	         delay(200);
	         digitalWrite(4, LOW);
	         state = CHECKING;
	      }
	      
	      if(buttonTwo == HIGH && !buttonTwoUsed) {
	         buttonTwoUsed = 1;
	         codeTry[1] = 2;
	         digitalWrite(4, LOW);
	         delay(200);
	         digitalWrite(4, HIGH);
	         delay(200);
	         digitalWrite(4, LOW);
	         state = CHECKING;
	      }
	      
	      if(millis() - start > 10000) {
	         digitalWrite(4, LOW);
	         state = LOCKED;
	      }
	      break;
	    
	    case CHECKING:
	    
	      if(code[0] == codeTry[0] && code[1] == codeTry[1]) {
	         digitalWrite(2, HIGH);
	         state = UNLOCKED;  
	      } else {
	         digitalWrite(7, HIGH);
	         delay(200);
	         digitalWrite(7, LOW);
	         state = LOCKED; 
	      }
	      break;
	         
	    case UNLOCKED:
	      delay(5000);
	      digitalWrite(2, LOW);
	      state = LOCKED;
		  break;
	  }
	}