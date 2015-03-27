INSTRUCTIONS

When somthing is hit by the say projectile they will begin their conversation numbered :1:

Also note you can only begin conversation with the NEUTRAL units




To make a conversation, start by labeling the first conversation like so

:X:
	//where X is the conversation number
	//NOTE: YOU MUST HAVE PRESSED ENTER AFTER THE 2nd COLON
	Next you write the text you want to be said.
My name Jeff.

	To make the conversation continue to a different persons line you do like so
:ENTITYTYPENUM->X;
	//where ENTITYTYPE is the entities type num as denoted by the struct in code
	//Just look for the ENTITYTYPE = part
	//and once again x is the conversation number
	
	//Use a Semicolon to denote the end of the stage

EXAMPLE

:1:
Hey there! Welcome to Sigma Six!
:0>7;