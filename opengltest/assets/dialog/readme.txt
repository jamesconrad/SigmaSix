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
:ENTITYTYPE->X:
	//where ENTITYTYPE is the entities type as denoted by the struct in code
	//and once again x is the conversation number

EXAMPLE

:1:
Hey there! Welcome to Sigma Six!
:PLAYER->7: