/*
 * Copyright 2010-2015 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *  http://aws.amazon.com/apache2.0
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

/**
 * @file subscribe_publish_sample.c
 * @brief simple MQTT publish and subscribe on the same topic
 *
 * This example takes the parameters from the aws_iot_config.h file and establishes a connection to the AWS IoT MQTT Platform.
 * It subscribes and publishes to the same topic - "sdkTest/sub"
 *
 * If all the certs are correct, you should see the messages received by the application in a loop.
 *
 * The application takes in the certificate path, host name , port and the number of times the publish should happen.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>

#include </home/pi/wiringPi/wiringPi/wiringPi.h>
//#include "mcp3008Spi.h"

#include "aws_iot_config.h"
#include "aws_iot_log.h"
#include "aws_iot_version.h"
#include "aws_iot_mqtt_client_interface.h"

#include "config.h"

//#define TRIG 29
//#define ECHO 28

int devicedetails=1,sensordetails=0;

void setup() {
//        wiringPiSetup();
        pinMode(controlpin1, OUTPUT);
	pinMode(controlpin2, OUTPUT);
        pinMode(sensorpin1, INPUT);
	pinMode(sensorpin2, INPUT);
	pinMode(sensorpin3, INPUT);
	pinMode(sensorpin4, INPUT);

        //TRIG pin must start LOW
   //     digitalWrite(TRIG, LOW);
     //   delay(30);
}
/*
int getCM() {
	setup();
        //Send trig pulse
        digitalWrite(TRIG, HIGH);
        delayMicroseconds(20);
        digitalWrite(TRIG, LOW);

        //Wait for echo start
        while(digitalRead(ECHO) == LOW);

        //Wait for echo end
        long startTime = micros();
        while(digitalRead(ECHO) == HIGH);
        long travelTime = micros() - startTime;

        //Get distance in cm
        int distance = travelTime / 58;

        return distance;
}*/
/**
 * @brief Default cert location
 */
char certDirectory[PATH_MAX + 1] = "../../../certs";

/**
 * @brief Default MQTT HOST URL is pulled from the aws_iot_config.h
 */
char HostAddress[255] = AWS_IOT_MQTT_HOST;

/**
 * @brief Default MQTT port is pulled from the aws_iot_config.h
 */
uint32_t port = AWS_IOT_MQTT_PORT;

/**
 * @brief This parameter will avoid infinite loop of publish and exit the program after certain number of publishes
 */
uint32_t publishCount = 0;

void iot_subscribe_callback_handler(AWS_IoT_Client *pClient, char *topicName, uint16_t topicNameLen,
									IoT_Publish_Message_Params *params, void *pData) {
	IOT_UNUSED(pData);
	IOT_UNUSED(pClient);
	IOT_INFO("Subscribe callback");
	IOT_INFO("%.*s\t%.*s", topicNameLen, topicName, (int) params->payloadLen, params->payload);
char controlstring1[100],controlstring2[100],controlstring3[100],controlstring4[100];
sprintf(controlstring1,"%s on",controlfeedname1);
sprintf(controlstring2,"%s off",controlfeedname1);
sprintf(controlstring3,"%s on",controlfeedname2);
sprintf(controlstring4,"%s off",controlfeedname2);

if(!strncmp(params->payload,controlstring1,strlen(controlstring1)))
	{
	digitalWrite(controlpin1, HIGH);
	IOT_INFO("%s is on",controlfeedname1);
	}
if(!strncmp(params->payload,controlstring2,strlen(controlstring2)))
        {
	digitalWrite(controlpin1, LOW);
	IOT_INFO("%s is off",controlfeedname1);
        }

if(!strncmp(params->payload,controlstring3,strlen(controlstring3)))
        {
	digitalWrite(controlpin2, HIGH);
	IOT_INFO("%s is on",controlfeedname2);
        }

if(!strncmp(params->payload,controlstring4,strlen(controlstring4)))
        {
	digitalWrite(controlpin2, LOW);
	IOT_INFO("%s is off",controlfeedname2);
        }

}

void disconnectCallbackHandler(AWS_IoT_Client *pClient, void *data) {
	IOT_WARN("MQTT Disconnect");
	IoT_Error_t rc = FAILURE;

	if(NULL == pClient) {
		return;
	}

	IOT_UNUSED(data);

	if(aws_iot_is_autoreconnect_enabled(pClient)) {
		IOT_INFO("Auto Reconnect is enabled, Reconnecting attempt will start now");
	} else {
		IOT_WARN("Auto Reconnect not enabled. Starting manual reconnect...");
		rc = aws_iot_mqtt_attempt_reconnect(pClient);
		if(NETWORK_RECONNECTED == rc) {
			IOT_WARN("Manual Reconnect Successful");
		} else {
			IOT_WARN("Manual Reconnect Failed - %d", rc);
		}
	}
}

void parseInputArgsForConnectParams(int argc, char **argv) {
	int opt;

	while(-1 != (opt = getopt(argc, argv, "h:p:c:x:"))) {
		switch(opt) {
			case 'h':
				strcpy(HostAddress, optarg);
				IOT_DEBUG("Host %s", optarg);
				break;
			case 'p':
				port = atoi(optarg);
				IOT_DEBUG("arg %s", optarg);
				break;
			case 'c':
				strcpy(certDirectory, optarg);
				IOT_DEBUG("cert root directory %s", optarg);
				break;
			case 'x':
				publishCount = atoi(optarg);
				IOT_DEBUG("publish %s times\n", optarg);
				break;
			case '?':
				if(optopt == 'c') {
					IOT_ERROR("Option -%c requires an argument.", optopt);
				} else if(isprint(optopt)) {
					IOT_WARN("Unknown option `-%c'.", optopt);
				} else {
					IOT_WARN("Unknown option character `\\x%x'.", optopt);
				}
				break;
			default:
				IOT_ERROR("Error in command line argument parsing");
				break;
		}
	}

}

int main(int argc, char **argv) {

//FILE *fp;
 

  /* close */
  //pclose(fp);
wiringPiSetup();
	bool infinitePublishFlag = true;
	int timedelay=1;
	char rootCA[PATH_MAX + 1];
	char clientCRT[PATH_MAX + 1];
	char clientKey[PATH_MAX + 1];
	char CurrentWD[PATH_MAX + 1];
	char cPayload[512];

	int32_t i = 0;

	IoT_Error_t rc = FAILURE;

	AWS_IoT_Client client;
	IoT_Client_Init_Params mqttInitParams = iotClientInitParamsDefault;
	IoT_Client_Connect_Params connectParams = iotClientConnectParamsDefault;

	IoT_Publish_Message_Params paramsQOS0;
	IoT_Publish_Message_Params paramsQOS1;

	parseInputArgsForConnectParams(argc, argv);

	IOT_INFO("\nPAASMER IoT SDK Version %d.%d.%d-%s\n", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH, VERSION_TAG);

	getcwd(CurrentWD, sizeof(CurrentWD));
	snprintf(rootCA, PATH_MAX + 1, "%s/%s/%s", CurrentWD, certDirectory, AWS_IOT_ROOT_CA_FILENAME);
	snprintf(clientCRT, PATH_MAX + 1, "%s/%s/%s", CurrentWD, certDirectory, AWS_IOT_CERTIFICATE_FILENAME);
	snprintf(clientKey, PATH_MAX + 1, "%s/%s/%s", CurrentWD, certDirectory, AWS_IOT_PRIVATE_KEY_FILENAME);

	IOT_DEBUG("rootCA %s", rootCA);
	IOT_DEBUG("clientCRT %s", clientCRT);
	IOT_DEBUG("clientKey %s", clientKey);
	mqttInitParams.enableAutoReconnect = false; // We enable this later below
	mqttInitParams.pHostURL = HostAddress;
	mqttInitParams.port = port;
	mqttInitParams.pRootCALocation = rootCA;
	mqttInitParams.pDeviceCertLocation = clientCRT;
	mqttInitParams.pDevicePrivateKeyLocation = clientKey;
	mqttInitParams.mqttCommandTimeout_ms = 20000;
	mqttInitParams.tlsHandshakeTimeout_ms = 5000;
	mqttInitParams.isSSLHostnameVerify = true;
	mqttInitParams.disconnectHandler = disconnectCallbackHandler;
	mqttInitParams.disconnectHandlerData = NULL;

	rc = aws_iot_mqtt_init(&client, &mqttInitParams);
	if(SUCCESS != rc) {
		IOT_ERROR("paasmer_iot_mqtt_init returned error : %d ", rc);
		return rc;
	}

	connectParams.keepAliveIntervalInSec = 10;
	connectParams.isCleanSession = true;
	connectParams.MQTTVersion = MQTT_3_1_1;
	connectParams.pClientID = AWS_IOT_MQTT_CLIENT_ID;
	connectParams.clientIDLen = (uint16_t) strlen(AWS_IOT_MQTT_CLIENT_ID);
	connectParams.isWillMsgPresent = false;

	IOT_INFO("Connecting...");
	rc = aws_iot_mqtt_connect(&client, &connectParams);
	if(SUCCESS != rc) {
		IOT_ERROR("Error(%d) connecting to %s:%d", rc, mqttInitParams.pHostURL, mqttInitParams.port);
		return rc;
	}
	/*
	 * Enable Auto Reconnect functionality. Minimum and Maximum time of Exponential backoff are set in aws_iot_config.h
	 *  #AWS_IOT_MQTT_MIN_RECONNECT_WAIT_INTERVAL
	 *  #AWS_IOT_MQTT_MAX_RECONNECT_WAIT_INTERVAL
	 */
	rc = aws_iot_mqtt_autoreconnect_set_status(&client, true);
	if(SUCCESS != rc) {
		IOT_ERROR("Unable to set Auto Reconnect to true - %d", rc);
		return rc;
	}

	IOT_INFO("Subscribing...");
	char sub_topic[100];
	sprintf(sub_topic,"%s_%s",UserName,DeviceName);
	rc = aws_iot_mqtt_subscribe(&client,sub_topic, strlen(sub_topic), QOS0, iot_subscribe_callback_handler, NULL);
	if(SUCCESS != rc) {
		IOT_ERROR("Error subscribing : %d ", rc);
		return rc;
	}

//	sprintf(cPayload, "%s : %d :%d cm", "hello from SDK", i, getCM());

	paramsQOS0.qos = QOS0;
	paramsQOS0.payload = (void *) cPayload;
	paramsQOS0.isRetained = 0;

	paramsQOS1.qos = QOS1;
	paramsQOS1.payload = (void *) cPayload;
	paramsQOS1.isRetained = 0;

	if(publishCount != 0) {
		infinitePublishFlag = false;
	}

	while((NETWORK_ATTEMPTING_RECONNECT == rc || NETWORK_RECONNECTED == rc || SUCCESS == rc)
		  && (publishCount > 0 || infinitePublishFlag)) {

		//Max time the yield function will wait for read messages
		rc = aws_iot_mqtt_yield(&client, 100);
		if(NETWORK_ATTEMPTING_RECONNECT == rc) {
			// If the client is attempting to reconnect we will skip the rest of the loop.
			continue;
		}

		IOT_INFO("-->sleep!");
		sleep(1);
		//timedelay=1;

//FILE *fp;
 // char path[1035];
  /* Open the command for reading. */
/*  fp = popen("/home/pi/tempm.py", "r");
  if (fp == NULL) {
    printf("Failed to run command\n" );
    exit(1);
  }
*/
  /* Read the output a line at a time - output it. */
 // while (fgets(path, sizeof(path)-1, fp) != NULL) {
   // printf("%s", path);
 // }
/*
while (!feof (fp))
    {  
      printf ("%d ", i);
      fscanf (fp, "%d", &d); 
 printf ("%d ", d);     
    }
*/









//	setup();
//	printf("Distance: %dcm\n", getCM());
//sprintf(cPayload,"{");
	//	sprintf(cPayload, "%s ", "sensor :US");
//sprintf(cPayload, "{\n\"sensorType\" : \"%s\",\n\"%s\" :  \"%d\"\n} ", "TEMP sensor", "sensorData",d);
if(UserName != "" && DeviceName !=""){
if (devicedetails==1){
sprintf(cPayload, "{\n\"username\" : \"%s\",\n\"devicename\" : \"%s\"\n}",UserName,DeviceName);
		paramsQOS0.payloadLen = strlen(cPayload);
//sprintf(cPayload, "{\n\"sensorType\" : \"%s\",\n\"%s\" :  \"%s\"\n} ", "TEMP sensor", "sensorData",path);
		rc = aws_iot_mqtt_publish(&client, "paasmer_device_details",22, &paramsQOS0);
		if(publishCount > 0) {
			publishCount--;
		}
devicedetails=0;
sensordetails=1;
}
//		sprintf(cPayload, "%s : %d :%d cm ", "hello from SDK QOS1", i++,getCM());
//sprintf(cPayload, "{\n\"sensorType\" : \"%s\",\n\"%s\" :  \"22\"\n} ", "US sensor", "sensorData");
else if (sensordetails==1){
if(((timedelay++)%timePeriod)==0){
int a = digitalRead(sensorpin1),b = digitalRead(sensorpin2),c = digitalRead(sensorpin3),d = digitalRead(sensorpin4);
sprintf(cPayload, "{\n\"feedname1\" : \"%s\",\n\"sensorvalue1\" : \"%d\",\n\"feedname2\" : \"%s\",\n\"sensorvalue2\" : \"%d\",\n\"feedname3\" : \"%s\",\n\"sensorvalue3\" : \"%d\",\n\"feedname4\" : \"%s\",\n\"sensorvalue4\" : \"%d\",\n\"username\" : \"%s\",\n\"devicename\" : \"%s\"\n}",feedname1,a,feedname2,b,feedname3,c,feedname4,d,UserName,DeviceName);
 //sprintf(cPayload, "{\n\"sensorType\" : \"%s\",\n\"%s\" :  \"%s\"\n} ", "TEMP sensor","sensorData",path);
		paramsQOS1.payloadLen = strlen(cPayload);
		rc = aws_iot_mqtt_publish(&client, "paasmer_sensor_details",22, &paramsQOS1);
		if (rc == MQTT_REQUEST_TIMEOUT_ERROR) {
			IOT_WARN("QOS1 publish ack not received.\n");
			rc = SUCCESS;
		}
		if(publishCount > 0) {
			publishCount--;
		}
}
}}

	}

	if(SUCCESS != rc) {
		IOT_ERROR("An error occurred in the loop.\n");
	} else {
		IOT_INFO("Publish done\n");
	}
//pclose(fp);

	return rc;
}
