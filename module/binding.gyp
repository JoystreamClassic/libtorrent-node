{
  'variables' : {
    'target%': ''
  },
  'targets': [{
      'target_name': 'custombuild',
      'target_type': 'none',
      'actions': [{
        'action_name': 'compile',
        'inputs': [],
        'outputs': [''],
        'action': ['node', 'build.js', '--nodedir=<@(nodedir)', '--target=<@(target)', '--arch=<@(target_arch)']
      }]
  }]
}
