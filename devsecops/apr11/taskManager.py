# File: task_manager.py

def create_task(task_name, description):
  """Creates a new task and returns a dictionary representing the task."""
  task = {
      "name": task_name,
      "description": description,
      "status": "open"  # Possible statuses: "open", "in progress", "completed"
  }
  return task

def update_task_status(task, new_status):
  """Updates the status of a given task."""
  if task and new_status in ["open", "in progress", "completed"]:
    task["status"] = new_status
    return True
  else:
    return False  # Indicate failure to update

def get_task_description(task):
  """Retrieves the description of a given task."""
  if task:
    return task["description"]
  else:
    return None

def delete_task(task_list, task_name):
  """Deletes a task from the task list based on its name."""
  for index, task in enumerate(task_list):
    if task["name"] == task_name:
      del task_list[index]
      return True  # Indicate successful deletion
  return False  # Indicate task not found