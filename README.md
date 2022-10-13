# HoloBLSD-Player V2

Proj kit:
Desktop Qt 5.15.2 MinGW 64-bit
Desktop Qt 6.3.1  MinGW 64-bit

```
Main - runs app

  ↳MainWindow - manage fileopener and tab creation
  
      ↳FileOpener - reads files and store info for timeline use
      
          ↳Activity - group of nodes, shows activity node from 
          
            ↳Nodes  - period of timei n which acti in dealt with
            
     ↳TabWidget - one for each user, one for all users
     
          ↳Summary - Global info from users' session (log file)
          
          ↳ActivityList - Listo of activity dealt with. to hide activity in timeline
          
          ↳Inspector  - info for each user for each activity
          
          ↳VideoPlayer  - plays recording of session
          
          ↳TimelineWidget - everithing timeline related
          
             ↳Timeline  - graohic representation of log file              -A BIT OF A MESS
             
                  ↳TimelineCursor - moves with video and controls it      
                  
              ↳TimelineToolbar  - all actions the user can perform      
              
                  ↳UserVisibilityButton - to hide users' nodes in timeline

```

# HoloBLSD-Player V1
A video player for the HoloBLSD project: this player is a debriefing tool for the v2 of the training tool.
The prototype has single video functions and allows to analyse one performance at a time.

Present Classes:
- Activities - Node Activities from start to finish
- ActivityEntry - All activities read from log files
- Events - Event Activities
- TimeLine - graphic representation of activities
- MainWindow - container for video and timeline

Soon-to-be Classes:
- VideoPlayer - to have one obj for each user
- User - to allow multi user debrief

Issues:
- Graphics artifact make te experince sub optimal
- video Lag in first seconds of play
- video no audio




