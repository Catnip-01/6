import tkinter as tk
from tkinter import ttk  # For themed widgets
import time
import struct

DEVICE_PATH = "/dev/memory_allocator"
FONT_FAMILY = "Consolas"  # Monospace font for technical look
BG_COLOR = "#2E3440"      # Dark background
FG_COLOR = "#ECEFF4"      # Light foreground
ACCENT_COLOR = "#81A1C1"  # Blue accent

def read_allocator_info():
    if use_hardcoded.get():
        kmalloc_addr = 0xCAFEBABE12345678
        kzalloc_addr = 0xDEADBEEF98765432
        vmalloc_addr = 0xF00DBABE11223344
        page_addr =    0xBEEFCAFE55667788
        update_ui(kmalloc_addr, kzalloc_addr, vmalloc_addr, page_addr)
        log_message("Using hardcoded test data.")
    else:
        try:
            with open(DEVICE_PATH, "rb") as f:
                data = f.read(struct.calcsize("QQQQ"))
                if data:
                    kmalloc_addr, kzalloc_addr, vmalloc_addr, page_addr = struct.unpack("QQQQ", data)
                    update_ui(kmalloc_addr, kzalloc_addr, vmalloc_addr, page_addr)
                else:
                    log_message("Error: Could not read data from kernel module.")
        except FileNotFoundError:
            log_message(f"Error: Device file '{DEVICE_PATH}' not found. Ensure module is loaded.")
        except Exception as e:
            log_message(f"Error reading device: {e}")
    root.after(500, read_allocator_info_with_logging)

def update_ui(kmalloc, kzalloc, vmalloc, page):
    kmalloc_label.config(text=f"kmalloc: 0x{kmalloc:016x}")
    kzalloc_label.config(text=f"kzalloc: 0x{kzalloc:016x}")
    vmalloc_label.config(text=f"vmalloc: 0x{vmalloc:016x}")
    page_label.config(text=f"Page:    0x{page:016x}")

root = tk.Tk()
root.title("Kernel Memory Monitor")
root.configure(bg=BG_COLOR)

# Apply a themed style
style = ttk.Style(root)
style.theme_use('clam')  # A clean, cross-platform theme

style.configure("TFrame", background=BG_COLOR) # Style for the frame
style.configure("TLabel", background=BG_COLOR, foreground=FG_COLOR, font=(FONT_FAMILY, 12))
style.configure("TCheckbutton", background=BG_COLOR, foreground=FG_COLOR, font=(FONT_FAMILY, 10))
style.configure("TButton", background=ACCENT_COLOR, foreground=BG_COLOR, font=(FONT_FAMILY, 10), padding=5)
style.configure("TEntry", background="#434C5E", foreground=FG_COLOR, font=(FONT_FAMILY, 10))
style.configure("TText", background="#434C5E", foreground=FG_COLOR, font=(FONT_FAMILY, 10))

content_frame = ttk.Frame(root, padding=15, style="TFrame")
content_frame.pack(expand=True, fill="both")

use_hardcoded = tk.BooleanVar()
check_hardcoded = ttk.Checkbutton(content_frame, text="Use Test Data", variable=use_hardcoded, style="TCheckbutton")
check_hardcoded.pack(pady=10, anchor="w")

labels_frame = ttk.Frame(content_frame, style="TFrame")
labels_frame.pack(pady=10, fill="x")

kmalloc_label = ttk.Label(labels_frame, text="kmalloc: N/A", style="TLabel")
kmalloc_label.pack(fill="x", pady=2)

kzalloc_label = ttk.Label(labels_frame, text="kzalloc: N/A", style="TLabel")
kzalloc_label.pack(fill="x", pady=2)

vmalloc_label = ttk.Label(labels_frame, text="vmalloc: N/A", style="TLabel")
vmalloc_label.pack(fill="x", pady=2)

page_label = ttk.Label(labels_frame, text="Page:    N/A", style="TLabel")
page_label.pack(fill="x", pady=2)

log_label = ttk.Label(content_frame, text="Log:", style="TLabel", anchor="w")
log_label.pack(fill="x", pady=(10, 2))

log_text = tk.Text(content_frame, height=5, width=50, bg="#434C5E", fg=FG_COLOR, font=(FONT_FAMILY, 10), bd=0)
log_text.pack(pady=5, fill="x")
log_text.insert(tk.END, "Monitoring kernel memory...\n")
log_text.config(state=tk.DISABLED)  # Make it read-only

def log_message(message):
    log_text.config(state=tk.NORMAL)
    log_text.insert(tk.END, message + "\n")
    log_text.see(tk.END)  # Scroll to the latest message
    log_text.config(state=tk.DISABLED)

def read_allocator_info_with_logging():
    if use_hardcoded.get():
        kmalloc_addr = 0xCAFEBABE12345678
        kzalloc_addr = 0xDEADBEEF98765432
        vmalloc_addr = 0xF00DBABE11223344
        page_addr =    0xBEEFCAFE55667788
        update_ui(kmalloc_addr, kzalloc_addr, vmalloc_addr, page_addr)
        log_message("Logging piped to 'output.txt'.")
    else:
        try:
            with open(DEVICE_PATH, "rb") as f:
                data = f.read(struct.calcsize("QQQQ"))
                if data:
                    kmalloc_addr, kzalloc_addr, vmalloc_addr, page_addr = struct.unpack("QQQQ", data)
                    update_ui(kmalloc_addr, kzalloc_addr, vmalloc_addr, page_addr)
                else:
                    log_message("Error: Could not read data from kernel module.")
        except FileNotFoundError:
            log_message(f"Error: Device file '{DEVICE_PATH}' not found. Ensure module is loaded.")
        except Exception as e:
            log_message(f"Error reading device: {e}")
    root.after(500, read_allocator_info_with_logging)

read_allocator_info_with_logging()

root.mainloop()