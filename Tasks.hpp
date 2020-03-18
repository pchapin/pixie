/*! \file    tasks.hpp
 *  \brief   Task manipulation.
 *  \author  Peter C. Chapin <pchapin@vtc.edu>
 */

#ifndef TASKS_HPP
#define TASKS_HPP

//! Initializes the task list.
void initialize_tasks( );

//! Releases any resources in use by the task list.
void cleanup_tasks( );

//! Add the specified number of minutes to the indicated task.
void add_minutes( int task_number, int additional_minutes );

//! Change the daily allocation of the indicated task to the new amount of minutes.
void change_daily( int task_number, int new_daily );

//! Change priority of the indicated task to the new priority level.
void change_priority( int task_number, int new_priority );

//! Create a task with the given description and priority. Other attributes are default.
void create_task( const std::string &new_description, int initial_priority );

//! Delete a task given it's index in the task list.
void delete_task( int task_number );

//! Rename the indicated task using the new description text.
void rename( int task_number, const std::string &new_description );

//! Save the tasks to the task list used during construction.
void save_tasks( );

//! Start working on the indicated task.
void start_task( int task_number );

//! Stop working on all active tasks.
void stop_tasks( );

//! Remove one day's worth of daily allocations.
void undo_daily( );

//! Zero accumulated times for all tasks. This also stops any active tasks.
void zero_tasks( );

//! Displays all the tasks.
void display_tasks( );

#endif
