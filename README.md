Facial Expression API Documentation
1. Introduction
This document outlines the API for connecting to a facial expression data collection service, which captures and transmits real-time facial expression data. The service utilizes a TCP connection on port 8065 to transmit structured data representing various facial expressions.
2. Connection Details
IP Address: [Collection end IP Address]
Port: 8061
3. Data Structure
The data is transmitted using a structured format defined by the following C++ struct:
typedef struct
{
    float bs[NUM_FACE_FEATURES];

}BSFACE;
Where `NUM_FACE_FEATURES` represents the total number of facial features being tracked, each float value within `bs` array corresponds to a specific facial feature's intensity.
4. Feature Indexes
Each index within the `bs` array corresponds to a specific facial feature as follows:
•	0 browDown_L
•	1 browDown_R
•	2 browInnerUp_L
•	3 browInnerUp_R
•	4 browOuterUp_L
•	5 browOuterUp_R
•	6 cheekPuff_L
•	7 cheekPuff_R
•	8 cheekSquint_L
•	9 cheekSquint_R
•	10 eyeBlink_L
•	11 eyeBlink_R
•	12 eyeLookDown_L
•	13 eyeLookDown_R
•	14 eyeLookIn_L
•	15 eyeLookIn_R
•	16 eyeLookOut_L
•	17 eyeLookOut_R
•	18 eyeLookUp_L
•	19 eyeLookUp_R
•	20 eyeSquint_L
•	21 eyeSquint_R
•	22 eyeWide_L
•	23 eyeWide_R
•	24 jawForward
•	25 jawLeft
•	26 jawOpen
•	27 jawRight
•	28 mouthClose
•	29 mouthDimple_L
•	30 mouthDimple_R
•	31 mouthFrown_L
•	32 mouthFrown_R
•	33 mouthFunnel
•	34 mouthLeft
•	35 mouthLowerDown_L
•	36 mouthLowerDown_R
•	37 mouthPress_L
•	38 mouthPress_R
•	39 mouthPucker
•	40 mouthRight
•	41 mouthRollLower
•	42 mouthRollUpper
•	43 mouthShrugLower
•	44 mouthShrugUpper
•	45 mouthSmile_L
•	46 mouthSmile_R
•	47 mouthStretch_L
•	48 mouthStretch_R
•	49 mouthUpperUp_L
•	50 mouthUpperUp_R
•	51 noseSneer_L
•	52 noseSneer_R
5. Connection Protocol
The connection and data transmission follow a specific protocol to ensure accurate and continuous data transfer.
5.1 Initial Connection
Upon establishing a TCP connection, the client should first send an empty packet header defined by the `HEADCALL` struct to keep the connection alive.
typedef struct
{
    int len;
    short reqType;
    short errorType;
    short v1;
} HEADCALL;
The `HEADCALL` struct is initialized with specific values to facilitate the connection handshake.
5.2 Receiving Data
After the initial connection is established, the client begins to receive data packets. The client should listen for packets with a length greater than 24 bytes, indicating that they contain facial expression data.
6. Example Code Snippets
C++ Example:
HEADCALL DL_head;
DL_head.len = 12;
DL_head.reqType = 1;
DL_head.errorType = 0;
DL_head.v1 = 1; 

int pshift = 0; 
int len = ReadInt32(buffer, pshift); pshift += 4; 
short reqType = ReadInt16(buffer, pshift); pshift += 2; 
short errorType = ReadInt16(buffer, pshift); pshift += 2; 
pshift += 16; 
if (len > 24) CopyFromexpressionStream(buffer, pshift);
C# Example:
HEADCALL DLD_head = new HEADCALL();
DLD_head.len = 12;
DLD_head.reqType = 1;
DLD_head.errorType = 0;
DLD_head.v1 = 1;

int pshift = 0; 
int len = ReadInt32(buffer, pshift); pshift += 4; 
short reqType = ReadInt16(buffer, pshift); pshift += 2; 
short errorType = ReadInt16(buffer, pshift); pshift += 2; 
pshift += 16; 
if (len > 24) CopyFromexpressionStream(buffer, pshift);

7. Conclusion
This documentation provides a comprehensive guide for connecting to and utilizing the facial expression data collection service. For further assistance or clarification, please contact the support team.
