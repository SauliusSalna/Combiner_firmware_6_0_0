void TaskList(byte task)      //runs tasks and incraments pointer if nessecary
{
  switch(task) {

    case 3: {
      AutoStart();
      break;
    }

  }
}



void AutoStart()
{
  TaskNumber=0;    // task is complete, task is deleted 
  delay(1000);
  LaserEnable();
}
