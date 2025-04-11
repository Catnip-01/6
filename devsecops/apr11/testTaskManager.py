# testTaskManager.py

import unittest
from taskManager import create_task, update_task_status, get_task_description, delete_task

class TestTaskManager(unittest.TestCase):
    def test_create_task(self):
        task = create_task("Task 1", "Description 1")
        self.assertEqual(task["name"], "Task 1")
        self.assertEqual(task["description"], "Description 1")
        self.assertEqual(task["status"], "open")

    def test_update_task_status(self):
        task = create_task("Task 2", "Description 2")
        self.assertTrue(update_task_status(task, "in progress"))
        self.assertEqual(task["status"], "in progress")
        self.assertFalse(update_task_status(task, "invalid"))  # Test the 'else'
        self.assertFalse(update_task_status(None, "completed")) # Test with None

    def test_get_task_description(self):
        task = create_task("Task 3", "Description 3")
        self.assertEqual(get_task_description(task), "Description 3") # Test if task exists
        self.assertIsNone(get_task_description(None)) # Test if task is None

    def test_delete_task(self):
        task_list = [create_task("Task 1", "Description 1"), create_task("Task 2", "Description 2")]
        self.assertTrue(delete_task(task_list, "Task 1"))
        self.assertEqual(len(task_list), 1)
        self.assertFalse(delete_task(task_list, "NonExistent Task"))
        self.assertEqual(len(task_list), 1)