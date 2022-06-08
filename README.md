# Display Presets

Store presets for multi-monitor configurations.

## Usage

### Store the currently active multi-monitor configuration as a preset

```
.\store.exe preset_name
```

Will create the file `preset_name`. This is a data file and can be moved/renamed.

### Apply a stored preset

```
.\load.exe preset_name
```

## Note

Presets *probably* are device/config specific. 
Do not expect them to transfer between machines or 
continue to work if displays are plugged into different ports
or after any other hardware changes.
